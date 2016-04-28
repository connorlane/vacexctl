#include <utilities.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include <config.h>
#include <adc.h>
#include <pwm.h>
#include <timerinterrupt.h>
#include <led.h>
#include <pump.h>
#include <button.h>
//#include <argon.h>
#include <air.h>


void loop()
{
	static int counter = 0;

	if (counter > 100) {
		LED_Toggle();
		counter = 0;
	}

	counter++;
}

int main(void)
{
	// Initialize hardware devices
	//Air_Init();
	//Argon_Init();
	//Button_Init();
	LED_Init();
	Pump_Init();

	TimerInterrupt_Init(10, loop);	
	
	// Interrupts, GO!
	sei();

	TimerInterrupt_Start();

	while (1) {
		while (!Button_Pressed()) {}
	
		Pump_On();		

		DelayMS(3500);

		Pump_Off();
	}
}

