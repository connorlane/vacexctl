#ifndef HX711_H
#define HX711_H

#include <config.h>
#include <utilities.h>
#include <stdint.h>

static int _gain;

static inline void _SetSck() { HX711_SCK_PORT |= (1 << HX711_SCK); }
static inline void _UnsetSck() { HX711_SCK_PORT &= ~(1 << HX711_SCK); }

static inline int _ReadDout() { return (HX711_DOUT_PIN & (1 << HX711_DOUT)) ? 1 : 0; };

void HX711_SetGain(int gain);
uint32_t HX711_Read();

void HX711_Init(int gain)
{
	// Set SCK direction
	HX711_SCK_DDR |= (1 << HX711_SCK);	

	// Set DOUT direction
	HX711_DOUT_DDR &= ~(1 << HX711_DOUT);	

	// Set gain
	HX711_SetGain(gain);
}

void HX711_SetGain(int gain)
{
	switch (gain)
	{
		case 128:
			_gain = 1;
			break;
		case 64:
			_gain = 3;
			break;
		case 32:
			_gain = 2;
			break;
		default:
			Error();
	}		

	// Set SCK low
	_UnsetSck();

	// Do an empty read to push the settings through
	HX711_Read();
}

int HX711_IsReady()
{
	return _ReadDout() == 0;
}

uint32_t HX711_Read()
{
	uint8_t data[3];

	while (!HX711_IsReady())
	{
		// Wait
	}

	// Read 24 bits of data
	for (int i = 3; i--;) {
		for (char c = 8; c--;) {
			_SetSck();
			_delay_us(1);
			if(_ReadDout())
				data[i] |= (1 << c);
			else
				data[i] &= ~(1 << c);
			_UnsetSck();
			_delay_us(1);
		}
	}

	// Set the channel and gain for the next reading
	for (int i = 0; i < _gain; i++) {
		_SetSck();
		_delay_us(1);
		_UnsetSck();
		_delay_us(1);
	}

	data[2] ^= 0x80;

	return ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];	
}

#endif
