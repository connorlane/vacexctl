#ifndef ARGON_H
#define ARGON_H

void Argon_Init() {
	// Set the led as output
	ARGON_DDR |= (1 << ARGON);
}

void Argon_On() {
	// Turn on LED
	ARGON_PORT |= (1 << ARGON);
}

void Argon_Off() {
	// Turn off LED
	ARGON_PORT &= ~(1 << ARGON);
}

#endif
