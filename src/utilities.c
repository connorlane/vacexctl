/*
 * utilities.cpp
 *
 * Created: 1/23/2014 11:07:22 PM
 *  Author: Connor
 */ 

#include "utilities.h"
#include "util/delay.h"

//void FlashSlow()
//{
//	uint8_t i;
//	for(i = 0; i < 2; i++)
//	{
//		PORTB = 0xFF;
//		Delay_MS(1000);
//		PORTB = 0x00;
//		Delay_MS(1000);
//	}
//}
//
//void FlashFast()
//{
//	uint8_t i;
//	for(i = 0; i < 10; i++)
//	{
//		PORTB = 0xFF;
//		Delay_MS(200);
//		PORTB = 0x00;
//		Delay_MS(200);
//	}
//}

void Error()
{
}

void DelayMS(long int delay)
{
	while(delay--) _delay_ms(1);
}

int IsValidCharacter(uint8_t data)
{
	return (
		(data >= '0' && data <= '9') || 
		(data >= 'A' && data <= 'Z') 
    );
}
