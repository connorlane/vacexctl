#ifndef PUMP_H
#define PUMP_H

void Pump_Init() {
	// Set the led as output
	PUMP_DDR |= (1 << PUMP);
}

void Pump_On() {
	// Turn on the pump
	PUMP_PORT |= (1 << PUMP);
}

void Pump_Off() {
	// Turn off the pump
	PUMP_PORT &= ~(1 << PUMP);
}

#endif
