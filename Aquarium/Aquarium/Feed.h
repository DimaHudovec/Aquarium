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
#include <LiquidCrystal.h>

struct FeedStruct
{
	int currentFeed; // стандартная настройка подкормки (отключено)
	int feedHour;
	int feedMinute;
	String currentFeedStr;
};

extern FeedStruct Feed;

void setFeed(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd);
void printSetFeed(LiquidCrystal &lcd, int &menuItemElement);
void changeFeedStr();
void initFeed();

#endif

