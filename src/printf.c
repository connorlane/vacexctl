#include <serial.h>
#include <printf.h>

FILE uart_output = FDEV_SETUP_STREAM(Serial_Write, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, Serial_Read, _FDEV_SETUP_READ);

void _Printf_Init()
{
	stdout = &uart_output;
	stdin = &uart_input;
}

