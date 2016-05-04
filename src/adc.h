#ifndef ADC_H
#define ADC_H

#include <stdint.h>

#ifndef ADC_INITIALIZED
#define ADC_INITIALIZED
#define ADC_Init() _ADC_Init()
#else
#define ADC_Init()
#endif

void _ADC_Init();

uint8_t ADC_Read(int channel);

#endif
