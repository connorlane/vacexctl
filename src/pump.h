#ifndef PUMP_H
#define PUMP_H

#ifndef PUMP_INITIALIZED
#define PUMP_INITIALIZED
#define Pump_Init() _Pump_Init()
#else
#define Pump_Init()
#endif

void _Pump_Init() {
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
