// 
// 
// 

#include "Air.h"

AirStruct Air;

void setAir(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd) // menuLevel = 2 - значит подменю главного меню
{
	if (menuLevel != 2 && menuItem != 4) return;
	deb();
	// Обработка нажатия кнопки меню (выход из пункта меню)
	switch (Button.lcd_key)
	{
	case btnSELECT:
		menuLevel = 1;
		menuItemElement = 0;
		delay(100);
		//lcd.clear();
		printMainMenu(lcd, menuItem);
		break;
	// Обработка нажатия кнопки "Вверх"
	case btnUP:
		Air.currentAir++;
		if (Air.currentAir > 3)
		{
			Air.currentAir = 0;
		}
		changeAirStr();
		delay(100);
		//lcd.clear();
		printSetAir(lcd);
		break;
	// Обработка нажатия кнопки "Вниз"
	case btnDOWN:
		Air.currentAir--;
		if (Air.currentAir < 0)
		{
			Air.currentAir = 3;
		}
		changeAirStr();
		delay(100);
		//lcd.clear();
		printSetAir(lcd);
		break;
	}
	// Обработка значений переменной освещения
}

void printSetAir(LiquidCrystal &lcd)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(" -  Air set   - ");
	lcd.setCursor(0, 1);
	lcd.print("Air:            ");
	lcd.setCursor(6, 1);
	lcd.print(Air.currentAirStr);
}

void changeAirStr()
{
	switch (Air.currentAir)
	{
	case 0:
		Air.currentAirStr = "OFF";
		break;
	case 1:
		Air.currentAirStr = "1h/1h";
		break;
	case 2:
		Air.currentAirStr = "1h/0,5h";
		break;
	case 3:
		Air.currentAirStr = "ON";
		break;
	}
}

void initAir()
{
	Air.currentAir = 0;
	Air.currentAirStr = "OFF";
}
