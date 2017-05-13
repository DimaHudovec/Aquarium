// Light.h

#ifndef _LIGHT_h
#define _LIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"
#include "MainMenu.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>

struct LightStruct
{
	byte currentLight; // стандартная настройка подсветки (отключено)
	byte realLight;
	String currentLightStr;
};

extern LightStruct Light;

void setLights(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd);
void printSetLights(LiquidCrystal &lcd);
void changeLightStr();
void initLight();
void swithlight();

#endif

