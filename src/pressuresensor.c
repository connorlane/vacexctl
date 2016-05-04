#include <pressuresensor.h>
#include <avr/io.h>
#include <adc.h>
#include <config.h>
#include <stdint.h>

void _PressureSensor_Init() {
	ADC_Init();
}

float PressureSensor_Get() {
	uint8_t adc_result = ADC_Read(PRESSURE_ADC_CHANNEL);
	if (adc_result > MIN_ADC_VALUE)
		adc_result = MIN_ADC_VALUE;

	float pressure_ratio = (float)(adc_result - MIN_ADC_VALUE) / (float)(MAX_ADC_VALUE - MIN_ADC_VALUE);
	float pressure = pressure_ratio * (MAX_PRESSURE - MIN_PRESSURE) + MIN_PRESSURE;
	
	return pressure;
}

