#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include "ringbuffer.h"

#ifndef SERIAL_INITIALIZED
#define SERIAL_INITIALIZED
#define Serial_Init() _Serial_Init()
#else
#define Sertial_Init()
#endif

void _Serial_Init();
void Serial_Write(uint8_t byte);
void Serial_PrintHex(uint8_t val);
void Serial_WriteBuffer(uint8_t* buf, int num);
uint8_t Serial_Read();
int Serial_Available();

#endif //SERIAL_H
