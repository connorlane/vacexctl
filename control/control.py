import serial
import time
import scipy.signal as signal
import numpy as np

KI = 2
KP = 1500

LOOP_PERIOD_MS = 100

TICKS_PER_GRAM = 422.75

FILTER_ORDER = 20
CUTOFF_FREQ = 0.2

ERROR_THRESH = 0.75

feedrate = 0.1 # grams / minute

def calculateChecksum(databytes):
	return -sum(databytes) & 0xFF

def getPacket():
	#while True:

	# Throw away anything before the start character
	while s.read() != ':':
		pass

	# Get the packet data
	datastring = s.readline().rstrip('\n')

	# Split out the message and checksum
	#message = datastring[:-2]
	#checksum = int(datastring[-2:], 16)

	# Interpret hex values to byte array 
	#  (I love python... I mean, damn. Look at how simple this is:)
	#databytes = map(ord, message.decode("hex"))

	# Make sure valid data	
	#if calculateChecksum(databytes) != checksum:
	#	print "Warning! Checksum error on received data: " + datastring
	#else:
	#	break
	
	return datastring
	
def sendPacket(cvstring):
	# Calculate the checksum
	#cvbytes = map(ord, cvstring.decode("hex"))

	# Generate checksum string
	#checksum = calculateChecksum(cvbytes)
	#checksumstring = format(checksum, 'x')
	
	# Send the packet	
	s.write(":" + cvstring + "\n")



s = serial.Serial(
	port='/dev/ttyUSB0',
	baudrate=19200,
	bytesize=serial.EIGHTBITS,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	timeout=1,
	xonxoff=False
)

initial_mass_samples = []

nyq = 1000 / (2*LOOP_PERIOD_MS)
filter_coefficients = signal.firwin(FILTER_ORDER, cutoff = CUTOFF_FREQ / nyq, window = "hamming")
history = np.zeros(FILTER_ORDER)

print "Measuring initial mass..."

for i in xrange(50):
	sendPacket("0000")
	initial_mass_samples.append(int(getPacket(), 16))
	
	time.sleep(LOOP_PERIOD_MS / 1000.0)

initialmass = sum(initial_mass_samples) / len(initial_mass_samples)
initialtime = time.time()

print "Initial Mass: " + str(initialmass)
print "Initial Time: " + str(initialtime)

cv = 0

Iterm = 0.0
Pterm = 0.0

while True:
	#if cv < 0:
	#	cv = 0

	# Encode control variable in hex format
	cvstring = "%.4X" % cv
	
	# Send the control variable
	sendPacket(cvstring)
	
	# Grab a packet
	packet = getPacket()
	
	# Interpret the process value
	pv = (int(packet, 16) - initialmass) / TICKS_PER_GRAM

	# Get the setpoint	
	current_time = time.time()
	setpoint = -(feedrate / 60.0) * (current_time - initialtime)

	# Please, for the love of god, fix this rediculous hack eventually...
	# This is here because I'm getting a weird error from the microcontroller where the signal drops down
	#    really low for a split second, then returns to normal. It's a problem with the firmware that
	#    needs to be fixed eventually, but this seems to work for now
	if abs(pv - setpoint) <= ERROR_THRESH:
		# Calculate the process error
		#error = pv_filtered - setpoint
		error = pv - setpoint

		# Record the sample
		history = np.roll(history, 1)
		history[0] = error

		# Apply low-pass filter
		error_filtered = sum(np.multiply(history, filter_coefficients))

		# Calculate PI control values
		Iterm = Iterm + error
		Pterm = error_filtered
		cv = KP * Pterm + KI * Iterm + 3000

		print str(current_time) + ", " + str(pv) + ", " + str(setpoint) + ", " + str(error_filtered) + ", " + str(cv)
	
	# Wait a few milliseconds
	time.sleep(LOOP_PERIOD_MS / 1000.0)
	
