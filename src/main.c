#include <utilities.h>
#include <util/delay.h> 
#include <avr/interrupt.h> 
#include <stdint.h>

#include <config.h>
#include <adc.h>
#include <timerinterrupt.h>
#include <led.h>
#include <pump.h>
#include <button.h>
#include <argon.h>
#include <air.h>
#include <pressuresensor.h>
#include <pressurefault.h>

int counter = 0;

void loop()
{
	if (counter > 100) {
		LED_Toggle();
		counter = 0;
	}

	counter++;
}

int main(void)
{
	// Initialize hardware devices
	Air_Init();
	Argon_Init();
	Button_Init();
	LED_Init();
	Pump_Init();
	PressureSensor_Init();
	PressureFault_Init();

	//TimerInterrupt_Init(10, loop);	
	
	// Interrupts, GO!
	sei();

	Argon_On();

	//TimerInterrupt_Start();

	//while(1) {
	//	Argon_On();
	//	_delay_ms(1000);
	//	Argon_Off();
	//	_delay_ms(1000);
	//}

	while (1) {
		if (PressureFault_Triggered())
			Argon_On();
		else
			Argon_Off();
	}
}

