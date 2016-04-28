#ifndef BUTTON_H
#define BUTTON_H

void Button_Init() {
	BUTTON_DDR &= ~(1 << BUTTON);
}

int Button_Pressed() {
	if (BUTTON_PIN & (1 << BUTTON)) 
		return 1;
	else
		return 0;
}

#endif
