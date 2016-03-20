from flowplot import FlowPlot, RandomData
import struct
import serial
import time

class SerialWrapper:
	#TAU = 1

	def __init__(self):
		self.title="Scale Plot"
		self.low=0.0
		self.high=100000

		self.ser = serial.Serial()
		self.ser.port = "/dev/ttyUSB0"
		self.ser.baudrate = 19200
		self.ser.bytesize =serial.EIGHTBITS
		self.ser.parity = serial.PARITY_NONE
		self.ser.stopbits = serial.STOPBITS_ONE
		self.ser.timeout = 1
		self.ser.xonxoff = False
	
		self.ser.open()

		#self.history = list()
		self.previous = 0
		self.ser.flushInput()

	def get(self):
		try:	
			self.ser.write(":3200\n")
			while self.ser.read() != ':':
				pass;

			raw = self.ser.readline().rstrip('\n')
			raw = raw.translate(None, '\x00')
			data = int(raw, 16)
			data = data - 8400000
			#print ":".join("{:02x}".format(ord(c)) for c in raw)
			#data = struct.unpack('<L', raw + "\0")[0]
			#normalized = (data - 0) / 1024.0
			#result = (data + self.TAU * self.previous) / (1 + self.TAU)
			#self.previous = result
			result = data
			print str(time.time()) + "," + str(result)
			return result
		except struct.error:
			return 0;

sw = SerialWrapper()

datasource = sw
fp = FlowPlot(datasource, 10, 25*10, 1280, 720)
fp.run();

#while(1):
#	sw = SerialWrapper()
#	print sw.get()

