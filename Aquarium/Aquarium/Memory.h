// Memory.h

#ifndef _MEMORY_h
#define _MEMORY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
	#include <EEPROM.h>


void MemWrite(int p_address, int p_value);
unsigned int MemRead(int p_address);
#endif

