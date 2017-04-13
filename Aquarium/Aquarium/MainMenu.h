// MainMenu.h

#ifndef _MAINMENU_h
#define _MAINMENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"
#include "MainScreen.h"
#include "Feed.h"
#include "Air.h"
#include "Temperature.h"
#include "Light.h"
#include <LiquidCrystal.h>

void mainMenu(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd);
void printMainMenu(LiquidCrystal &lcd, int &menuItem);
void printSub(int &menuItem, int &menuItemElement, LiquidCrystal &lcd);

#endif

