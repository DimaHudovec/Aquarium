// 
// 
// 

#include "Temperature.h"

TemperatureStruct Temperature;

void setTemp(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd) // menuLevel = 2 - ������ ������� �������� ����
{
	if (menuLevel != 2 && menuItem != 2) return;
	deb();
	// ��������� ������� ������ ���� (����� �� ������ ����)
	switch (Button.lcd_key)
	{
	case btnSELECT:
		menuLevel = 1;
		menuItemElement = 0;
		delay(100);
		//lcd.clear();
		MemWrite(8, Temperature.currentTemp);
		EEPROM.write(10, Temperature.currentHeater);
		printMainMenu(lcd, menuItem);
		break;
		// ��������� ������� ������ "������" (����� ����������� �������� ������)
	case btnRIGHT:
		menuItemElement++;
		if (menuItemElement > 1)
		{
			menuItemElement = 0;
		}
		delay(100);
		//lcd.clear();
		printSetTemp(lcd, menuItemElement);
		break;
		// ��������� ������� ������ "�����" (����� ����������� �������� �����)
	case btnLEFT:
		menuItemElement--;
		if (menuItemElement < 0)
		{
			menuItemElement = 1;
		}
		delay(100);
		//lcd.clear();
		printSetTemp(lcd, menuItemElement);
		break;
		// ��������� ������� ������ "�����" (��������� �����)
	case btnUP:
		if (menuItemElement == 0) // ��������� �����������
		{
			if (Temperature.currentTemp < 35)
			{
				Temperature.currentTemp++;
			}
			delay(100);
			//lcd.clear();
		}
		if (menuItemElement == 1) // ��������� ������ (������)
		{
			Temperature.currentHeater++;
			if (Temperature.currentHeater > 1)
			{
				Temperature.currentHeater = 0;
			}
			changeTempStr();
			delay(100);
			//lcd.clear();
		}
		printSetTemp(lcd, menuItemElement);
		break;
		// ��������� ������� ������ "����" (��������� �����)
	case btnDOWN:
		if (menuItemElement == 0) // ��������� �����������
		{
			if (Temperature.currentTemp > 15)
			{
				Temperature.currentTemp--;
			}
			delay(100);
			//lcd.clear();
		}
		if (menuItemElement == 1) // ��������� ������ (������)
		{
			Temperature.currentHeater--;
			if (Temperature.currentHeater < 0)
			{
				Temperature.currentHeater = 1;
			}
			changeTempStr();
			delay(100);
			//lcd.clear();
		}
		printSetTemp(lcd, menuItemElement);
		break;
	}
}

void printSetTemp(LiquidCrystal &lcd, int &menuItemElement)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(" -  Temp set  - ");
	lcd.setCursor(0, 1);
	if (menuItemElement == 0)
	{
		lcd.print("Temperature:  oC");
		lcd.setCursor(12, 1);
		lcd.print(Temperature.currentTemp);
	}
	if (menuItemElement == 1)
	{
		lcd.print("  Heating:      ");
		lcd.setCursor(11, 1);
		lcd.print(Temperature.currentTempStr);
	}
}

void changeTempStr()
{
	switch (Temperature.currentHeater)
	{
	case 0:
		Temperature.currentTempStr = "OFF";
		break;
	case 1:
		Temperature.currentTempStr = "ON";
		break;
	}
}

void initTemp()
{
	unsigned int temp = MemRead(8);
	if (temp == 65535)
	{
		Temperature.currentTemp = 23;
		Temperature.currentHeater = 0;
		Temperature.currentTempStr = "OFF";
		Temperature.realTemp = 0;
	}
	else
	{
		Temperature.currentHeater = EEPROM.read(10);
		changeTempStr();
		Temperature.currentTemp = temp;
	}	
}

void readTemp(OneWire &ds)
{
	byte data[2];
	ds.reset();
	ds.write(0xCC);
	ds.write(0x44);
	delay(750);
	ds.reset();
	ds.write(0xCC);
	ds.write(0xBE);
	data[0] = ds.read();
	data[1] = ds.read();
	Temperature.realTemp = (data[1] << 8) + data[0];
	Temperature.realTemp = Temperature.realTemp >> 4;
}
