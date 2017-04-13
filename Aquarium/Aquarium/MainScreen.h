// MainScreen.h
#include "MyRTC.h"

#ifndef _MAINSCREEN_h
#define _MAINSCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"
#include "Feed.h"
#include "Air.h"
#include "Temperature.h"
#include "Light.h"
#include "MainMenu.h"
#include <LiquidCrystal.h>

struct MainScreenStruct
{
	int screen;
};

extern MainScreenStruct MainScreen;

 // переменная выбора экрана
void mainScreen(int &menuLevel, int &menuItem, LiquidCrystal &lcd);
void printMainScreen(LiquidCrystal &lcd);
#endif

