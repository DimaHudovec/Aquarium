// 
// 
// 

#include "MainScreen.h"

MainScreenStruct MainScreen;

void mainScreen(int &menuLevel, int &menuItem, LiquidCrystal &lcd) // menuLevel = 0 - значит не меню, а главный экран
{
	if (menuLevel != 0) return;
	deb();
	// Обработка нажатия кнопки вызова меню ("MENU")
	switch (Button.lcd_key)
	{
	case btnSELECT:
		menuLevel = 1;
		MainScreen.screen = 0;
		delay(100);
		printMainMenu(lcd, menuItem);
		break;
		// Обработка нажатия кнопки "Вправо" ("RIGHT")
	case btnRIGHT:
		MainScreen.screen++;
		if (MainScreen.screen > 2)
		{
			MainScreen.screen = 0;
		}
		delay(100);
		printMainScreen(lcd);
		//lcd.clear();
		break;
		// Обработка нажатия кнопки "Влево" ("LEFT")
	case btnLEFT:
		MainScreen.screen--;
		if (MainScreen.screen < 0)
		{
			MainScreen.screen = 2;
		}
		delay(100);
		printMainScreen(lcd);
		//lcd.clear();
		break;
	}
}

void printMainScreen(LiquidCrystal &lcd)
{
	//lcd.clear();
	lcd.setCursor(0, 0);
	if (MyRTC.currentDay < 10)
	{
		lcd.print("0");
	}
	lcd.print(MyRTC.currentDay);
	lcd.print(".");
	if (MyRTC.currentMonth < 10)
	{
		lcd.print("0");
	}
	lcd.print(MyRTC.currentMonth);
	lcd.print(".");
	lcd.print(MyRTC.currentYear);
	lcd.print(" ");
	if (MyRTC.currentHour < 10)
	{
		lcd.print("0");
	}
	lcd.print(MyRTC.currentHour);
	lcd.print(":");
	if (MyRTC.currentMinute < 10)
	{
		lcd.print("0");
	}
	lcd.print(MyRTC.currentMinute);
	lcd.setCursor(0, 1);
	if (MainScreen.screen == 0)
	{
		lcd.print("t=");
		if (Temperature.realTemp < 10)
		{
			lcd.print("0");
		}
		lcd.print(int(Temperature.realTemp));
		lcd.print("oC L=");
		lcd.print(Light.currentLightStr);
		lcd.print("    ");
	}
	if (MainScreen.screen == 1)
	{
		lcd.print("Air:");
		lcd.print(Air.currentAirStr);
		lcd.print(" ");
		lcd.print("Heat:");
		lcd.print(Temperature.currentTempStr);
		lcd.print("    ");
	}
	if (MainScreen.screen == 2)
	{
		lcd.print("Feed:");
		lcd.print(Feed.currentFeedStr);
		lcd.print("        ");
	}
}