// Feed.h

#ifndef _FEED_h
#define _FEED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"
#include "MainMenu.h"
#include "MyRTC.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Servo.h>

struct FeedStruct
{
	byte currentFeed; // стандартная настройка подкормки (отключено)
	byte feedHour;
	byte feedMinute;
	byte feedToday;
	byte feedDay;
	String currentFeedStr;
	byte deg;
};

extern FeedStruct Feed;

void setFeed(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd, Servo &servo);
void printSetFeed(LiquidCrystal &lcd, int &menuItemElement);
void changeFeedStr();
void initFeed(Servo &servo);
void feeding(Servo &servo);

#endif

