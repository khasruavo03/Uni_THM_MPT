/*
 * Praktikum4.c
 *
 * Created: 11/05/2026 16:56:18
 * Author : khush
 */ 

#define F_CPU 24000000 
#include <avr/io.h>
#include "I2C_LCD.h"
#include <util/delay.h>

#define SPEED 200

int main(void)
{
	lcd_init();
	lcd_backlight(true);
	lcd_clear();
	
	uint8_t pos;
	uint8_t row;

	while (1)
	{
		// Obere Zeile: Von links nach Rechts
		for(pos = 0; pos < 16; pos++) 
		{
			lcd_moveCursor(0, 0);
			
			for (row = 0; row < 16; row++)
			{
				if(row == pos)
				{
					lcd_putChar('1');
				}
				else
				{
					lcd_putChar('0');
				}
			}
			lcd_moveCursor(0,1);
			for (row = 0; row < 16; row++)
			{
				lcd_putChar('0');
			}
			
			_delay_ms(SPEED);
		}
		
		// Untere Zeile: Von Rechts nach links
		for(pos = 15; pos < 16; pos--)
		{
			lcd_moveCursor(0,0);
			for(row = 0; row < 16; row++)
			{
				lcd_putChar('0');
			}
			lcd_moveCursor(0,1);
			for(row = 0; row < 16; row++)
			{
				if(row == pos)
				{
					lcd_putChar('1');
				}
				else 
				{
					lcd_putChar('0');
				}
			}
			_delay_ms(SPEED);
			if(pos == 0) {break;}
		}
	}
}