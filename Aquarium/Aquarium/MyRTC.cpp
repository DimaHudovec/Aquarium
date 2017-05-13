// 
// 
// 

#include "MyRTC.h"

MyRTCStruct MyRTC;

void setDate(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd, RTC_DS1307 &RTC)
{
	if (menuLevel != 2 && menuItem != 0) return;// menuLevel = 2 - ������ ������� �������� ����
	deb();
	// ��������� ������� ������ ���� (����� �� ������ ����)
	switch (Button.lcd_key)
	{
	case btnSELECT:
		menuLevel = 1;
		menuItemElement = 0;
		delay(100);
		//lcd.clear();
		setRealTime(RTC);
		printMainMenu(lcd, menuItem);
		break;
		// ��������� ������� ������ "������" (����� ����������� �������� ������)
	case btnRIGHT:
		menuItemElement++;
		if (menuItemElement > 2)
		{
			menuItemElement = 0;
		}
		delay(100);
		//lcd.clear();
		printSetDate(lcd);
		break;
		// ��������� ������� ������ "�����" (����� ����������� �������� �����)
	case btnLEFT:
		menuItemElement--;
		if (menuItemElement < 0)
		{
			menuItemElement = 2;
		}
		delay(100);
		//lcd.clear();
		printSetDate(lcd);
		break;
		// ��������� ������� ������ "�����" (��������� �����)
	case btnUP:
		if (menuItemElement == 0) // ��������� �������� ���
		{
			if ((MyRTC.currentMonth == 1) || (MyRTC.currentMonth == 3) || (MyRTC.currentMonth == 5) || (MyRTC.currentMonth == 7) || (MyRTC.currentMonth == 8) || (MyRTC.currentMonth == 10) || (MyRTC.currentMonth == 12))
			{
				MyRTC.currentDay++;
				if (MyRTC.currentDay > 31)
				{
					MyRTC.currentDay = 1;
				}
			}
			else if ((MyRTC.currentMonth == 2) && ((MyRTC.currentYear % 4 == 0 && MyRTC.currentYear % 100 != 0) || MyRTC.currentYear % 400 == 0))
			{
				MyRTC.currentDay++;
				if (MyRTC.currentDay > 29)
				{
					MyRTC.currentDay = 1;
				}
			}
			else if ((MyRTC.currentMonth == 2) && (MyRTC.currentYear % 4 != 0 || (MyRTC.currentYear % 100 == 0 && MyRTC.currentYear % 400 != 0)))
			{
				MyRTC.currentDay++;
				if (MyRTC.currentDay > 28)
				{
					MyRTC.currentDay = 1;
				}
			}

			else if ((MyRTC.currentMonth == 4) || (MyRTC.currentMonth == 6) || (MyRTC.currentMonth == 9) || (MyRTC.currentMonth == 11))
			{
				MyRTC.currentDay++;
				if (MyRTC.currentDay > 30)
				{
					MyRTC.currentDay = 1;
				}
			}
			delay(100);
			//lcd.clear();
		}

		if (menuItemElement == 1) // ��������� �������� ������
		{
			MyRTC.currentMonth++;
			if (MyRTC.currentMonth > 12)
			{
				MyRTC.currentMonth = 1;
			}
			delay(100);
			//lcd.clear();
		}

		if (menuItemElement == 2) // ��������� �������� ����
		{
			if (MyRTC.currentYear < 2117) // ����� 100 ��� �����������!)
			{
				MyRTC.currentYear++;
			}
			delay(100);
			//lcd.clear();
		}
		printSetDate(lcd);
		break;
		// ��������� ������� ������ "����" (��������� �����)
	case btnDOWN:
		if (menuItemElement == 0) // ��������� �������� ���
		{
			if ((MyRTC.currentMonth == 1) || (MyRTC.currentMonth == 3) || (MyRTC.currentMonth == 5) || (MyRTC.currentMonth == 7) || (MyRTC.currentMonth == 8) || (MyRTC.currentMonth == 10) || (MyRTC.currentMonth == 12))
			{
				MyRTC.currentDay--;
				if (MyRTC.currentDay < 1)
				{
					MyRTC.currentDay = 31;
				}
			}
			else if ((MyRTC.currentMonth == 2) && ((MyRTC.currentYear % 4 == 0 && MyRTC.currentYear % 100 != 0) || MyRTC.currentYear % 400 == 0))
			{
				MyRTC.currentDay--;
				if (MyRTC.currentDay < 1)
				{
					MyRTC.currentDay = 29;
				}
			}

			else if ((MyRTC.currentMonth == 2) && (MyRTC.currentYear % 4 != 0 || (MyRTC.currentYear % 100 == 0 && MyRTC.currentYear % 400 != 0)))
			{
				MyRTC.currentDay--;
				if (MyRTC.currentDay < 1)
				{
					MyRTC.currentDay = 28;
				}
			}
			else if ((MyRTC.currentMonth == 4) || (MyRTC.currentMonth == 6) || (MyRTC.currentMonth == 9) || (MyRTC.currentMonth == 11))
			{
				MyRTC.currentDay--;
				if (MyRTC.currentDay < 1)
				{
					MyRTC.currentDay = 30;
				}
			}
			delay(100);
			//lcd.clear();
		}

		if (menuItemElement == 1) // ��������� �������� ������
		{
			MyRTC.currentMonth--;
			if (MyRTC.currentMonth < 1)
			{
				MyRTC.currentMonth = 12;
			}
			delay(100);
			//lcd.clear();
		}

		if (menuItemElement == 2) // ��������� �������� ����
		{
			if (MyRTC.currentYear > 2017) // ����� 100 ��� �����������!)
			{
				MyRTC.currentYear--;
			}
			delay(100);
			//lcd.clear();
		}
		printSetDate(lcd);
		break;
	}
}

void setTime(int &menuLevel, int &menuItem, int &menuItemElement, LiquidCrystal &lcd, RTC_DS1307 &RTC) // menuLevel = 2 - ������ ������� �������� ����
{
	if (menuLevel != 2 && menuItem != 1) return;
	deb();
	// ��������� ������� ������ ���� (����� �� ������ ����)
	switch (Button.lcd_key)
	{
	case btnSELECT:
		menuLevel = 1;
		menuItemElement = 0;
		delay(100);
		//lcd.clear();
		setRealTime(RTC);
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
		printSetTime(lcd);
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
		printSetTime(lcd);
		break;
		// ��������� ������� ������ "�����" (��������� �����)
	case btnUP:
		if (menuItemElement == 0) // ��������� �����
		{
			MyRTC.currentHour++;
			if (MyRTC.currentHour > 23)
			{
				MyRTC.currentHour = 0;
			}
			delay(100);
			//lcd.clear();
		}

		else if (menuItemElement == 1) // ��������� �����
		{
			MyRTC.currentMinute++;
			if (MyRTC.currentMinute > 59)
			{
				MyRTC.currentMinute = 0;
			}
			delay(100);
			//lcd.clear();
		}
		printSetTime(lcd);
		break;
		// ��������� ������� ������ "����" (��������� �����)
	case btnDOWN:
		if (menuItemElement == 0) // ��������� �����
		{
			MyRTC.currentHour--;
			if (MyRTC.currentHour == 255 )
			{
				MyRTC.currentHour = 23;
			}
			delay(100);
			//lcd.clear();
		}

		else if (menuItemElement == 1) // ��������� �����
		{
			MyRTC.currentMinute--;
			if (MyRTC.currentMinute == 255)
			{
				MyRTC.currentMinute = 59;
			}
			delay(100);
			//lcd.clear();
		}
		printSetTime(lcd);
		break;
	}
}

void printSetDate(LiquidCrystal &lcd)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(" -  Date set  - ");
	lcd.setCursor(0, 1);
	lcd.print("Today:");
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
}

void printSetTime(LiquidCrystal &lcd)
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print(" -  Time set  - ");
	lcd.setCursor(0, 1);
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
}

void initMyRTC()
{
	MyRTC.currentDay = 1;
	MyRTC.currentMonth = 1;
	MyRTC.currentYear = 2017;
	MyRTC.currentHour = 12;
	MyRTC.currentMinute = 0;
}

void setRealTime(RTC_DS1307 & RTC)
{
	RTC.adjust(DateTime(uint16_t(MyRTC.currentYear), uint8_t(MyRTC.currentMonth),
		uint8_t(MyRTC.currentDay), uint8_t(MyRTC.currentHour), uint8_t(MyRTC.currentMinute),0));
}

void getRealTime(DateTime & now)
{
	MyRTC.currentYear = now.year();
	MyRTC.currentMonth = now.month();
	MyRTC.currentDay = now.day();
	MyRTC.currentHour = now.hour();
	MyRTC.currentMinute = now.minute();
}