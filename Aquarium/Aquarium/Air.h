// Air.h

#ifndef _AIR_h
#define _AIR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"
#include "MainMenu.h"
#include <LiquidCrystal.h>

struct AirStruct
{
	int currentAir; // стандартная настройка компрессора (отключено)
	String currentAirStr;
};

extern AirStruct Air;

void setAir(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd);
void printSetAir(LiquidCrystal &lcd);
void initAir();
void changeAirStr();
#endif

