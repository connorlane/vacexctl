#ifndef ARGON_H
#define ARGON_H

void Argon_Init() {
	// Set the pin as output
	ARGON_DDR |= (1 << ARGON);
}

void Argon_On() {
	// Turn pin on
	ARGON_PORT |= (1 << ARGON);
}

void Argon_Off() {
	// Turn pin off
	ARGON_PORT &= ~(1 << ARGON);
}

#endif

