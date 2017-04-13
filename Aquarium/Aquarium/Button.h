// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

struct ButtonStruct
{
	int adc_key_in;
	int lcd_key;
	int last;
};

extern ButtonStruct Button;

void deb();
void initButton();

#endif

