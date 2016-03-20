#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#ifndef PWM_INITIALIZED
#define PWM_INITIALIZED
#define PWM_Init() _PWM_Init()
#else
#define PWM_Init()
#endif

void _PWM_Init();

void PWM_Start();

void PWM_Stop();

void PWM_Write(uint16_t ontime_ns, uint16_t offtime_ns);

#endif


