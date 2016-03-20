import csv
import sys

TABLE_FILE = 'volts_to_ontime.csv'

output = ""

START = 1650
SPACING = 50

def linearInterpolate(x, x1, x2, y1, y2):
	return (x - x1)*(y2 - y1)/(x2 - x1) + y1


with open(TABLE_FILE, 'r') as tablefile:
	tablefilereader = csv.reader(tablefile, delimiter=',')
	
	target_voltage = START

	row = tablefilereader.next()

	previous_voltage, previous_ontime = 0, 0
	this_voltage, this_ontime = int(row[0]), int(row[1])

	target_ontime = linearInterpolate(target_voltage, previous_voltage, this_voltage, previous_ontime, this_ontime)
	output = output + "\t" + str(target_ontime)
	target_voltage = target_voltage + SPACING

	for row in tablefilereader:
		previous_voltage, previous_ontime = this_voltage, this_ontime
		this_voltage, this_ontime = int(row[0]), int(row[1])

		while(target_voltage < this_voltage):
			target_ontime = linearInterpolate(target_voltage, previous_voltage, this_voltage, previous_ontime, this_ontime)
			output = output + ",\n\t" + str(target_ontime)
			target_voltage = target_voltage + SPACING
			END = target_voltage

PREAMBLE = """
#ifndef HVTABLE_H
#define HVTABLE_H

#include <stdint.h>

#define HVTABLE_START """ + str(START) + """
#define HVTABLE_SPACING """ + str(SPACING) + """
#define HVTABLE_END """ + str(END) + """

uint16_t hvtable[] = {"""

POSTAMBLE = """
};

#endif"""

print PREAMBLE

print output

print POSTAMBLE
