#include <pressurefault.h>
#include <avr/io.h>

void PressureFault_Init() {
	PRESSUREFAULT_DDR &= ~(1 << PRESSUREFAULT);
}

int PressureFault_Triggered() {
		if (PRESSUREFAULT_PIN & (1 << PRESSUREFAULT))
			return 1;
		else
			return 0;
}

