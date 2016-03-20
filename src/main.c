#include <utilities.h>
#include <serial.h>
#include <util/delay.h>
#include <stdint.h>

#include <config.h>
#include <status.h>
#include <hx711.h>
#include <adc.h>
#include <pwm.h>
#include <hv.h>
#include <pulse.h>
#include <printf.h>
#include <timerinterrupt.h>
#include <voltagefilter.h>
#include <hx711filter.h>

//void hx711loop()
//{
//	uint8_t adcData;
//	int voltage;
//
//	// Read the HV feedback channel
//	adcData = ADC_Read(HVFEEDBACK_CHANNEL);
//
//	// Get the actual voltage. Must divide by 16 because the conversion
//	//   ratio is multiplied by 16 for accuracy. (Right shift by 4 is division
//	//   by 16).
//	voltage = (adcData * HV_CONVERSION_RATIO_x16) >> 4;
//
//	Serial_Write(':');
//	Serial_PrintHex((uint8_t) (voltage >> 8) & 0xFF);
//	Serial_PrintHex((uint8_t) voltage & 0xFF);	
//	Serial_Write('\n');
//}

static VoltageFilter voltageFilter;
static HX711Filter hx711Filter;

void loop()
{
	long hx711data;

	// Read the mass feedback
	hx711data = HX711_Read();
	
	HX711Filter_put(&hx711Filter, hx711data);
}

int main(void)
{
	long filteredMass;
	uint8_t data;
	char serdata[16];
	int setpoint;
	
	Status_Init();
	HX711_Init(128);	
	Serial_Init();
	Printf_Init();
	TimerInterrupt_Init(20, loop);	
	VoltageFilter_Init(&voltageFilter);
	HX711Filter_init(&hx711Filter);
	HV_Init();
	
	// Interrupts, GO!
	sei();

	HV_SetVoltage(1700);
	
	printf("Getting ready freddy...\n");
	TimerInterrupt_Start();
	DelayMS(3000);

	//HV_On();
	
	while(1)
	{
		do {
			while (Serial_Read() != ':');
		
			int i = 0;
			do {
				data = Serial_Read();
				serdata[i] = data;
				i++;
			} while (i < 15 && data != '\r' && data != '\n');
			serdata[i] = '\0';
		} while (sscanf(serdata, "%X", &setpoint) != 1);
		
		if (setpoint > 1700 && setpoint < 4600)	{
			printf("HVON\n");
			HV_SetVoltage(setpoint);
			HV_On();
		}
		else {
			printf("OFF\n");
			HV_Off();
		}
		
		TimerInterrupt_EnterCrit();
		filteredMass = HX711Filter_get(&hx711Filter);
		TimerInterrupt_ExitCrit();

		Serial_Write(':');	
		Serial_PrintHex((uint8_t) (filteredMass >> 16) & 0xFF);	
		Serial_PrintHex((uint8_t) (filteredMass >> 8) & 0xFF);	
		Serial_PrintHex((uint8_t) filteredMass & 0xFF);	
		Serial_Write('\n');
	}
}

