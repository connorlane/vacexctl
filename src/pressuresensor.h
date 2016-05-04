#ifndef PRESSURESENSOR_H
#define PRESSURESENSOR_H

#include <stdint.h>

#ifndef PRESSURESENSOR_INITIALIZED
#define PRESSURESENSOR_INITIALIZED
#define PressureSensor_Init() _PressureSensor_Init()
#else
#define PressureSensor_Init()
#endif

void _PressureSensor_Init();

float PressureSensor_Get();

#endif
