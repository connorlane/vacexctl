## FlowPlot - A utility for plotting a stream of data from a data source.
## Todd Sparks 
## 1 December 2015

import pygame
from pygame.locals import *  
import sys
import random
import numpy

class RandomData():
	'''data source class'''
	def __init__(self):
		print "random data source initialized"
		self.title="NUMPY Random Number Generator"
		self.low=0.0 # minimum value
		self.high=1.0 # maximum value
	def get(self):
		return numpy.random.random()

class FlowPlot():
	def __init__(self,source,rate,points,xres,yres):
		# initialize the screen and set up my data structures
		# 
		#syntax:
		#	source - data source object.  It MUST return a float or int with a .get() method
		#	rate - frame rate of the display in frames per second.  The utility will attempt to capture 1 new data point per screen update
		#	points - the number of points to draw across the plot
		#	xres - horizontal width of the plot, in pixels
		#	yres - vertical height of the plot, in pixels
		if xres<points:
			points=xres
			print "WARNING:insufficient resolution to display desired number of data points"
		self.screen = pygame.display.set_mode((xres, yres))
		self.datasource=source
		self.xres=xres
		self.yres=yres
		self.xscale=self.xres/float(points)
		self.yscale=float(self.yres)/(self.datasource.high-self.datasource.low)
		self.yoffset=self.datasource.low*self.yscale
		self.data=[yres for i in range(points)] # set all the data points to be at the bottom
		self.rate=rate
	
	def updateData(self):
		self.data.pop(0) # remove the oldest point
		self.data.append(self.yres-int(self.yscale*self.datasource.get()+self.yoffset)) # append a new point, scaled to the display

	def run(self):
		clock = pygame.time.Clock()
		pygame.font.init()
		font = pygame.font.SysFont("Arial",24)
		pause=False
		while True:
			keyState = pygame.key.get_pressed()
			for event in pygame.event.get():
				if event.type == pygame.QUIT:
					sys.exit()
				if keyState[pygame.K_UP]:
					self.yoffset-=int(self.yres/20) # move 5% up
				
				if keyState[pygame.K_DOWN]:
					self.yoffset+=int(self.yres/20) # move 5% down
				
				if keyState[pygame.K_KP_PLUS]:
					self.yscale*=1.05 # scale up 5% 
				
				if keyState[pygame.K_KP_MINUS]:
					self.yscale*=0.95 # scale down 5% 
				
				if keyState[pygame.K_r]: # reset scale and offset values to the defaults defined by the data source
					self.yscale=self.yres/(self.datasource.high-self.datasource.low)
					self.yoffset=self.datasource.low*self.yscale
				
				if keyState[pygame.K_SPACE]: # toggle pause
					if pause:
						pause=False
					else:
						pause=True
				

			clock.tick(self.rate)
			
			if not(pause):
				self.updateData()
				self.screen.fill((200, 200, 200)) # fill the screen white
				
				# draw the graph
				for i in range(len(self.data)-1):
					#print [i*self.xscale,self.data[i]],[(i+1)*self.xscale,self.data[i+1]]
					pygame.draw.line(self.screen,(0,255,0),[i*self.xscale,self.data[i]],[(i+1)*self.xscale,self.data[i+1]],3)
					
				# draw the title
				tw,th=font.size(self.datasource.title)
				self.screen.blit(font.render(self.datasource.title,-1,(0, 0, 0)),((self.xres-tw)/2,1))
				
				# draw the vertical scale
				# mid line
				pygame.draw.aaline(self.screen,(0,0,0),[0,self.yres/2],[self.xres,self.yres/2],True)
				self.screen.blit(font.render("{:4.3f}".format((self.yres/2-self.yoffset)/float(self.yscale)),-1,(0, 0, 0)),(0,self.yres/2-25))
				# 1/4 line
				pygame.draw.aaline(self.screen,(0,0,0),[0,self.yres*0.75],[self.xres,self.yres*0.75],True)
				self.screen.blit(font.render("{:4.3f}".format((self.yres/4-self.yoffset)/float(self.yscale)),-1,(0, 0, 0)),(0,self.yres*3/4-25))
				# 3/4 line
				pygame.draw.aaline(self.screen,(0,0,0),[0,self.yres/4],[self.xres,self.yres/4],True)
				self.screen.blit(font.render("{:4.3f}".format((self.yres*3/4-self.yoffset)/float(self.yscale)),-1,(0, 0, 0)),(0,self.yres/4-25))
				
				# draw the horizontal scale
				# mid line
				pygame.draw.aaline(self.screen,(0,0,0),[self.xres/2,25],[self.xres/2,self.yres],True)
				self.screen.blit(font.render("{:4.3f}s".format((self.xres/2)/float(self.rate)/self.xscale),-1,(0, 0, 0)),(self.xres/2,self.yres-25))
				# 3/4 line
				pygame.draw.aaline(self.screen,(0,0,0),[self.xres/4,25],[self.xres/4,self.yres],True)
				self.screen.blit(font.render("{:4.3f}s".format((self.xres*3/4)/float(self.rate)/self.xscale),-1,(0, 0, 0)),(self.xres/4,self.yres-25))
				# 1/4 line
				pygame.draw.aaline(self.screen,(0,0,0),[self.xres*0.75,25],[self.xres*0.75,self.yres],True)
				self.screen.blit(font.render("{:4.3f}s".format((self.xres/4)/float(self.rate)/self.xscale),-1,(0, 0, 0)),(self.xres*.75,self.yres-25))
				

				pygame.display.update()
			
		

if __name__ == "__main__":
	datasource=RandomData()
	plotter=FlowPlot(datasource,30,100,1280,720)
	plotter.run()