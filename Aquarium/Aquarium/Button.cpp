// 
// 
// 

#include "Button.h"

ButtonStruct Button;

void initButton()
{
	Button.adc_key_in = 5;
	Button.lcd_key = 5;
	Button.last = 5;
}

int read_LCD_buttons()
{
	int adc_key_in = analogRead(0);      // read the value from the sensor
									 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
									 // we add approx 50 to those values and check to see if we are close
	if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
										   // For V1.1 us this threshold
	if (adc_key_in < 60)   return btnRIGHT;
	if (adc_key_in < 200)  return btnUP;
	if (adc_key_in < 400)  return btnDOWN;
	if (adc_key_in < 600)  return btnLEFT;
	if (adc_key_in < 800)  return btnSELECT;

	return btnNONE;  // when all others fail, return this...
}

void deb()
{
	int current = read_LCD_buttons();
	if (Button.last != current)
	{
		delay(100);
		current = read_LCD_buttons();
	}
	Button.lcd_key = current;
	Button.last = current;
}

