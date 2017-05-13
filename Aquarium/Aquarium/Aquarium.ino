/*
 Name:		Aquarium.ino
 Created:	12.04.2017 16:06:16
 Author:	hudov
*/

// the setup function runs once when you press reset or power the board
#include "MySD.h"
#include "Memory.h"
#include <OneWire.h>
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
#include "MainMenu.h"
#include "MyRTC.h"
#include "MainScreen.h"
#include <Servo.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
OneWire ds(44);
RTC_DS1307 RTC;
DateTime dt;

int tempRelay = 36;
byte changed = 0;
Servo servo;
byte hourwrsd = 0;



int i = 0;

int menuLevel = 0; // переменна€ уровн€ меню
int menuItem = 0; // переменна€ пункта меню
int menuItemElement = 0; // переменна€ выбранного элемента пункта меню

void setup() {
	pinMode(tempRelay, OUTPUT);
	digitalWrite(tempRelay, HIGH);
	pinMode(34, OUTPUT);
	digitalWrite(34, HIGH);
	pinMode(35, OUTPUT);
	digitalWrite(35, HIGH);
	pinMode(53, OUTPUT);
	servo.attach(45);
	Serial.begin(9600);
	lcd.begin(16, 2);     // инициализаци€ LCD включаем подсветку
						  // ¬ывод приветстви€
	lcd.print("    AQUARIUM   ");
	Wire.begin();
	RTC.begin();
	initButton();
	initMyRTC();
	initAir();
	initFeed(servo);
	initLight();
	initTemp();
	// задержка
	delay(1000);
	
	RTC.adjust(DateTime(__DATE__, __TIME__));
	readTemp(ds);
	printMainScreen(lcd);
	
}

// the loop function runs over and over again until power down or reset
void loop() {	
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
			setFeed(menuLevel, menuItem, menuItemElement, lcd, servo);
			break;
		}
		break;
	}

	dt = RTC.now();
	if (dt.second() % 10 == 0 && menuLevel == 0)
	{
		readTemp(ds);
		if (Temperature.currentHeater == 1)
		{
			if (Temperature.realTemp < Temperature.currentTemp)
				digitalWrite(tempRelay, LOW);
			if (Temperature.realTemp >= Temperature.currentTemp)
				digitalWrite(tempRelay, HIGH);
		}
		if (dt.minute() == 0 && hourwrsd != dt.hour())
		{
			hourwrsd = dt.hour();
			writeTemp();
		}

		if (Feed.currentFeed > 0 && dt.hour() == Feed.feedHour && dt.minute() == Feed.feedMinute && Feed.feedDay != dt.day())
		{
			Feed.feedDay = dt.day();
			feeding(servo);
			writeFeed();
		}
		swithlight();
		swithair();
		getRealTime(dt);
		if(MainScreen.screen == 0)
			printMainScreen(lcd);
	}
}
