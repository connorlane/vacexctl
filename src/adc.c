#include <adc.h>

#include <avr/io.h>
#include <config.h>

void _ADC_Init()
{
	// AVcc with external capacitor at AREF pin
	// Left aligned bit (we only want 8 bits)
	ADMUX |= (1 << REFS0)|(1 << ADLAR);

	// Prescaler 64, turn on ADC
	//  -> 312.5 kilohertz @ F_CPU=20MHz
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADEN);
}

uint8_t ADC_Read(int channel)
{	
	// Select the adc channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);

	// Single conversion mode
	ADCSRA |= (1 << ADSC);

	// Wait until ADC conversion is complete
	while (ADCSRA & (1 << ADSC));

	// Read and return the result
	// ADLAR is enabled, so we just need the high eight bits
	return ADCH;
}


