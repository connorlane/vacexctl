#include <stdio.h>

#ifndef PRINTF_H
#define PRINTF_H

#ifndef PRINTF_INITIALIZED
#define PRINTF_INITIALIZED
#define Printf_Init() _Printf_Init()
#else
#define Printf_Init()
#endif

void _Printf_Init();

#endif
