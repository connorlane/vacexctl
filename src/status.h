#ifndef STATUS_H
#define STATUS_H

#include <utilities.h>

void Status_Init();

void Status_Set(int value);

void Status_Flash(int num, long int freq_millihertz);

#endif
