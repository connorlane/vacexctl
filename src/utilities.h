/*
 * Utilities.h
 *
 * Created: 1/23/2014 11:07:37 PM
 *  Author: Connor
 */ 

#ifndef UTILITIES_H
#define UTILITIES_H

#include "avr/io.h"
#include <util/delay.h>

//class RingBufferHandler;
//bool isCommandForCnc(RingBufferHandler& buf);
//
//void SendCurrentBuffer(SoftwareSerial& serial, RingBufferHandler& buf);
//
//void SayOK();
//
//void FlashFast();
//void FlashSlow();
//
void Error();

void DelayMS(long int delay);

//
int IsValidCharacter(uint8_t data);

#endif /* UTILITIES_H_ */
