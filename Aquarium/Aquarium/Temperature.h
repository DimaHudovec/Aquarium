// Temperature.h

#ifndef _TEMPERATURE_h
#define _TEMPERATURE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"
#include "MainMenu.h"
#include <OneWire.h>
#include <LiquidCrystal.h>

struct TemperatureStruct
{
	int currentTemp; // стандартная настройка температуры воды (отключено)
	int currentHeater;
	int realTemp;
	String currentTempStr;
};

extern TemperatureStruct Temperature;

void setTemp(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd);
void printSetTemp(LiquidCrystal &lcd, int &menuItemElement);
void changeTempStr();
void readTemp(OneWire &ds);
void initTemp();
#endif

