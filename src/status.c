#include "status.h"
#include "config.h"

void Status_Init()
{
	// Set the direction
	LED0_DDR |= (1 << LED0);

	// Turn it off
	LED0_PORT &= ~(LED0);
}

void Status_Set(int value)
{
	if (value)
		LED0_PORT |= (1 << LED0);
	else
		LED0_PORT &= ~(1 << LED0);
}

void Status_Flash(int num, long int freq_millihertz)
{
	if(num == 0)
		return;

	long int t_half_period = 1000000 / freq_millihertz;	

	for(int i = 0; i < num - 1; i++)
	{
		Status_Set(1);
		DelayMS(t_half_period);
		Status_Set(0);
		DelayMS(t_half_period);
	}

	Status_Set(1);
	DelayMS(t_half_period);
	Status_Set(0);
}

