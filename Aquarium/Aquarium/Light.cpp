// 
// 
// 

#include "Light.h"

LightStruct Light;

void setLights(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd) // menuLevel = 2 - значит подменю главного меню
{
	if (menuLevel != 2 && menuItem != 3) return;
	deb();
	// Обработка нажатия кнопки меню (выход из пункта меню)
	switch (Button.lcd_key)
	{
	case btnSELECT:
		menuLevel = 1;
		menuItemElement = 0;
		delay(100);
		EEPROM.write(0, Light.currentLight);
		switch (Light.currentLight)
		{
		case 0:
			digitalWrite(34, HIGH);
			break;
		case 2:
			digitalWrite(34, LOW);
			break;
		default:
			break;
		}
		//lcd.clear();
		printMainMenu(lcd, menuItem);
		break;
		// Обработка нажатия кнопки "Вверх"
	case btnUP:
		Light.currentLight++;
		if (Light.currentLight > 2)
		{
			Light.currentLight = 0;
		}
		changeLightStr();
		delay(100);
		//lcd.clear();
		printSetLights(lcd);
		break;
		// Обработка нажатия кнопки "Вниз"
	case btnDOWN:
		Light.currentLight--;
		if (Light.currentLight < 0)
		{
			Light.currentLight = 2;
		}
		changeLightStr();
		delay(100);
		//lcd.clear();
		printSetLights(lcd);
		break;
	}
}

void printSetLights(LiquidCrystal &lcd)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(" - Lights set - ");
	lcd.setCursor(0, 1);
	lcd.print(" Lights:        ");
	lcd.setCursor(9, 1);
	lcd.print(Light.currentLightStr);
}

void changeLightStr()
{
	// Обработка значений переменной освещения
	switch (Light.currentLight)
	{
	case 0:
		Light.currentLightStr = "OFF";
		break;
	case 1:
		Light.currentLightStr = "Sensor";
		break;
	case 2:
		Light.currentLightStr = "ON";
		break;
	}
	
}

void initLight()
{
	byte light = EEPROM.read(0);
	if (light == 255)
	{
		Light.currentLight = 0;
		Light.currentLightStr = "OFF";
	}
	else
	{
		Light.currentLight = light;
		changeLightStr();
		switch (Light.currentLight)
		{
		case 0:
			digitalWrite(34, HIGH);
			break;
		case 2:
			digitalWrite(34, LOW);
			break;
		default:
			break;
		}
	}
}

void swithlight()
{
	Serial.println(analogRead(12));
	if (Light.currentLight == 1 && analogRead(12) < 450 && Light.realLight == 0)
	{
		digitalWrite(34, LOW);
		Light.realLight = 1;
	}

	if (Light.currentLight == 1 && analogRead(12) > 400 && Light.realLight == 1)
	{
		digitalWrite(34, HIGH);
		Light.realLight = 0;
	}
}