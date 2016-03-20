#ifndef HV_H
#define HV_H

#include <pwm.h>
#include <pulse.h>
#include <adc.h>
#include <hvtable.h>

#include <stdio.h>

static const int _SAMPLE_FREQUENCY = 100;
static const int _PULSE_PERIOD = 10000;

static int _currentVoltage;

void HV_Init()
{
	ADC_Init();
	Pulse_Init();

	PWM_Write(6000, 11750);
}

void HV_SetVoltage(int volts)
{
	int hvtable_index;
	int ontime, offtime;

	if (volts < HVTABLE_START || volts >= HVTABLE_END)
		return;

	hvtable_index = (volts - HVTABLE_START) / HVTABLE_SPACING;

	ontime = ((volts - HVTABLE_START) % HVTABLE_SPACING)*(hvtable[hvtable_index + 1] - hvtable[hvtable_index])/HVTABLE_SPACING + hvtable[hvtable_index];
	offtime = _PULSE_PERIOD - ontime;

	_currentVoltage = volts;
	Pulse_Set(offtime, ontime);
}

void HV_On()
{
	Pulse_Start();
}

void HV_Off()
{
	Pulse_Stop();
}

#endif
