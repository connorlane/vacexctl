#ifndef AIR_H
#define AIR_H

void Air_Init() {
	// Set the led as output
	AIR_DDR |= (1 << AIR);
}

void Air_On() {
	// Turn on LED
	AIR_PORT |= (1 << AIR);
}

void Air_Off() {
	// Turn off LED
	AIR_PORT &= ~(1 << AIR);
}

#endif
