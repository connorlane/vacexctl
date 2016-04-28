#ifndef LED_H
#define LED_H

void LED_Init() {
	// Set the led as output
	LED_DDR |= (1 << LED);
}

void LED_Toggle() {
	LED_PORT ^= (1 << LED);
}

void LED_On() {
	// Turn on LED
	LED_PORT |= (1 << LED);
}

void LED_Off() {
	// Turn off LED
	LED_PORT &= ~(1 << LED);
}

#endif
