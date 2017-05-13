// MyRTC.h

#ifndef _MYRTC_h
#define _MYRTC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Button.h"
#include "MainMenu.h"
#include <LiquidCrystal.h>
#include <RTClib.h>

struct MyRTCStruct
{
	 byte currentDay; // стандартная настройка даты
	 byte currentMonth;
	 int currentYear;

	 byte currentHour; // стандартная настройка времени
	 byte currentMinute;

};

extern MyRTCStruct MyRTC;

void setTime(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd, RTC_DS1307 &RTC);
void setDate(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd, RTC_DS1307 &RTC);
void printSetTime(LiquidCrystal &lcd);
void printSetDate(LiquidCrystal &lcd);
void initMyRTC();
void setRealTime(RTC_DS1307 &RTC);
void getRealTime(DateTime &now);

#endif

