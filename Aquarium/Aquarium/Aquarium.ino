/*
 Name:		Aquarium.ino
 Created:	12.04.2017 16:06:16
 Author:	hudov
*/

// the setup function runs once when you press reset or power the board
#include <OneWire.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
//#include "Feed.h"
//#include "Air.h"
//#include "Temperature.h"
//#include "Light.h"
//#include "Button.h"
#include "MainMenu.h"
#include "MyRTC.h"
#include "MainScreen.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
OneWire ds(44);
RTC_DS1307 RTC;
DateTime dt;


int i = 0;

int menuLevel = 0; // переменна€ уровн€ меню
int menuItem = 0; // переменна€ пункта меню
int menuItemElement = 0; // переменна€ выбранного элемента пункта меню

void setup() {
	lcd.begin(16, 2);     // инициализаци€ LCD включаем подсветку
						  // ¬ывод приветстви€
	lcd.print("    AQUARIUM   ");
	Wire.begin();
	RTC.begin();
	initButton();
	initMyRTC();
	initAir();
	initFeed();
	initLight();
	initTemp();
	// задержка
	delay(1000);
	readTemp(ds);
	printMainScreen(lcd);
	
}

// the loop function runs over and over again until power down or reset
void loop() {
	if (RTC.now().minute() != MyRTC.currentMinute)
	{
		getRealTime(RTC);
		readTemp(ds);
		printMainScreen(lcd);
		
	}
	
	switch (menuLevel)
	{
	case 0:
		mainScreen(menuLevel,menuItem,lcd);
		break;
	case 1:
		mainMenu(menuLevel, menuItem, menuItemElement,lcd);
		break;
	case 2:
		switch (menuItem)
		{
		case 0:
			setDate(menuLevel, menuItem, menuItemElement, lcd, RTC);
			break;
		case 1:
			setTime(menuLevel, menuItem, menuItemElement, lcd, RTC);
			break;
		case 2:
			setTemp(menuLevel, menuItem, menuItemElement, lcd);
			break;
		case 3:
			setLights(menuLevel, menuItem, menuItemElement, lcd);
			break;
		case 4:
			setAir(menuLevel, menuItem, menuItemElement, lcd);
			break;
		case 5:
			setFeed(menuLevel, menuItem, menuItemElement, lcd);
			break;
		}
		break;
	}
}
