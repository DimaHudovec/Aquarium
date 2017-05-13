// 
// 
// 

#include "Feed.h"

FeedStruct Feed;

void setFeed(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd, Servo &servo) // menuLevel = 2 - значит подменю главного меню
{
	if (menuLevel != 2 && menuItem != 5) return;
	deb();
	// Обработка нажатия кнопки меню (выход из пункта меню)
	switch (Button.lcd_key)
	{
	case btnSELECT:
		menuLevel = 1;
		menuItemElement = 0;
		delay(100);
		//lcd.clear();
		EEPROM.write(2, Feed.currentFeed);
		EEPROM.write(3, Feed.feedHour);
		EEPROM.write(4, Feed.feedMinute);
		Feed.feedDay = 0;
		Feed.deg = 5;
		EEPROM.write(5, Feed.deg);
		EEPROM.write(6, Feed.currentFeed);
		servo.write(Feed.deg);
		printMainMenu(lcd, menuItem);
		break;
		// Обработка нажатия кнопки "Вправо" (выбор изменяемого элемента справа)
	case btnRIGHT:
		menuItemElement++;
		if (menuItemElement > 2)
		{
			menuItemElement = 0;
		}
		delay(100);
		//lcd.clear();
		printSetFeed(lcd, menuItemElement);
		break;
		// Обработка нажатия кнопки "Влево" (выбор изменяемого элемента слева)
	case btnLEFT:
		menuItemElement--;
		if (menuItemElement < 0)
		{
			menuItemElement = 2;
		}
		delay(100);
		//lcd.clear();
		printSetFeed(lcd, menuItemElement);
		break;
		// Обработка нажатия кнопки "Вверх" (увеличить число)
	case btnUP:
		if (menuItemElement == 0) // установка режима кормления
		{
			Feed.currentFeed++;
			if (Feed.currentFeed > 2)
			{
				Feed.currentFeed = 0;
			}
			changeFeedStr();
			delay(100);
			//lcd.clear();
		}

		if (menuItemElement == 1) // установка часов кормления
		{
			Feed.feedHour++;
			if (Feed.feedHour > 23)
			{
				Feed.feedHour = 0;
			}
			delay(100);
			//lcd.clear();
		}

		if (menuItemElement == 2) // установка минут кормления
		{
			Feed.feedMinute++;
			if (Feed.feedMinute > 59)
			{
				Feed.feedMinute = 0;
			}
			delay(100);
			//lcd.clear();
		}
		printSetFeed(lcd, menuItemElement);
		break;
		// Обработка нажатия кнопки "Вниз" (уменьшить число)
	case btnDOWN:
		if (menuItemElement == 0) // установка режима кормления
		{
			Feed.currentFeed--;
			if (Feed.currentFeed < 0)
			{
				Feed.currentFeed = 2;
			}
			changeFeedStr();
			delay(100);
			//lcd.clear();
		}

		if (menuItemElement == 1) // установка часов кормления
		{
			Feed.feedHour--;
			if (Feed.feedHour == 255)
			{
				Feed.feedHour = 23;
			}
			delay(100);
			//lcd.clear();
		}

		if (menuItemElement == 2) // установка минут кормления
		{
			Feed.feedMinute--;
			if (Feed.feedMinute == 255)
			{
				Feed.feedMinute = 59;
			}
			delay(100);
			//lcd.clear();
		}
		printSetFeed(lcd, menuItemElement);
		break;
	}
	// Обработка значений переменной освещения
}

void printSetFeed(LiquidCrystal &lcd, int &menuItemElement)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(" -Feeding set - ");
	lcd.setCursor(0, 1);
	if (menuItemElement == 0)
	{
		lcd.print("Auto:           ");
		lcd.setCursor(5, 1);
		lcd.print(Feed.currentFeedStr);
	}
	if (menuItemElement == 1 || menuItemElement == 2)
	{
		lcd.print(" Time:          ");
		lcd.setCursor(10, 1);
		if (Feed.feedHour < 10)
		{
			lcd.print("0");
		}
		lcd.print(Feed.feedHour);
		lcd.print(":");
		if (Feed.feedMinute < 10)
		{
			lcd.print("0");
		}
		lcd.print(Feed.feedMinute);
	}
}

void changeFeedStr()
{
	switch(Feed.currentFeed)
	{
	case 0:
		Feed.currentFeedStr = "OFF";
		break;
	case  1:
		Feed.currentFeedStr = "1time/day";
		break;
	case 2:
		Feed.currentFeedStr = "1time/2days";
		break;
	}
}

void initFeed(Servo &servo)
{
	byte mode = EEPROM.read(2);
	if (mode == 255)
	{
		Feed.currentFeed = 0;
		Feed.feedHour = 8;
		Feed.feedMinute = 0;
		Feed.currentFeedStr = "OFF";
		Feed.feedDay = 0;
		Feed.feedToday = Feed.currentFeed;
		Feed.deg = 5;
		servo.write(Feed.deg);
	}
	else
	{
		Feed.currentFeed = mode;
		Feed.feedHour = EEPROM.read(3);
		Feed.feedMinute = EEPROM.read(4);
		changeFeedStr();
		Feed.feedDay = 0;
		Feed.feedToday = EEPROM.read(6);
		if (Feed.feedToday == 255)
			Feed.feedToday = Feed.currentFeed;
		Feed.deg = EEPROM.read(5);
		if (Feed.deg == 255)
			Feed.deg = 5;
		servo.write(Feed.deg);
	}
}

void feeding(Servo &servo)
{
	switch (Feed.currentFeed)
	{
	case 1:
		if (Feed.feedToday == 1)
		{
			Serial.println("OK");
			switch (Feed.deg)
			{
			case 5:
				Feed.deg = 60;
				servo.write(Feed.deg);
				EEPROM.write(5, Feed.deg);
				break;
			case 60:
				Feed.deg = 120;
				servo.write(Feed.deg);
				EEPROM.write(5, Feed.deg);
				break;
			case 120: 
				Feed.deg = 180;
				servo.write(Feed.deg);
				delay(2000);
				Feed.deg = 5;
				servo.write(Feed.deg);
				EEPROM.write(5, Feed.deg);
				break;
			}
		}
		break;
	case 2:
		if (Feed.feedToday == 1)
		{
			Feed.feedToday = 2;
			EEPROM.write(6, Feed.feedToday);
			switch (Feed.deg)
			{
			case 5:
				Feed.deg = 60;
				servo.write(Feed.deg);
				EEPROM.write(5, Feed.deg);
				break;
			case 60:
				Feed.deg = 120;
				servo.write(Feed.deg);
				EEPROM.write(5, Feed.deg);
				break;
			case 120:
				Feed.deg = 180;
				servo.write(Feed.deg);
				delay(2000);
				Feed.deg = 5;
				servo.write(Feed.deg);
				EEPROM.write(5, Feed.deg);
				break;
			}
		}
		else if (Feed.feedToday == 2)
		{
			Feed.feedToday = 1;
			EEPROM.write(6, Feed.feedToday);
		}
		break;
	default:
		break;
	}
}