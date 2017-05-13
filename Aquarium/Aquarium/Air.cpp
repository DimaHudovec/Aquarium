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
		EEPROM.write(11, Air.currentAir);
		switch (Air.currentAir)
		{
		case 0:
			digitalWrite(35, HIGH);
			break;
		case 3:
			digitalWrite(35, LOW);
			break;
		default:
			break;
		}
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
		Air.currentAirStr = "1/1";
		break;
	case 2:
		Air.currentAirStr = "2/2";
		break;
	case 3:
		Air.currentAirStr = "ON";
		break;
	}
}

void initAir()
{
	byte air = EEPROM.read(11);
	if (air == 255)
	{
		Air.currentAir = 0;
		Air.currentAirStr = "OFF";
		Air.realAir = 0;
	}
	else
	{
		Air.currentAir = air;
		changeAirStr();
		Air.realAir = 0;
		if (Air.currentAir == 1 || Air.currentAir == 2)
			swithair();
		else if (Air.currentAir == 3)
			digitalWrite(35, LOW);
	}

}


void swithair()
{
	switch (Air.currentAir)
	{
	case 1:
		if (MyRTC.currentHour % 2 == 0 && Air.realAir == 0)
		{
			digitalWrite(35, LOW);
			Air.realAir = 1;
		}
		else if (MyRTC.currentHour % 2 != 0 && Air.realAir == 1)
		{
			digitalWrite(35, HIGH);
			Air.realAir = 0;
		}
		break;
	case 2:
		if ((MyRTC.currentHour % 4 == 0 || (MyRTC.currentHour - 1) % 4 == 0) && Air.realAir == 0)
		{
			digitalWrite(35, LOW);
			Air.realAir = 1;
		}
		else if (MyRTC.currentHour % 4 != 0 && Air.realAir == 0)
		{
			digitalWrite(35, HIGH);
			Air.realAir = 0;
		}
		break;
	default:
		break;
	}
}

