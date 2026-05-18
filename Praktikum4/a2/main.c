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

#define DELAY_MS 300

// Von Integer zur String
// Warum Buffer? -> Buffer ist ein Zeichenarray 
// (char[]), in dem die Zahl als Text gespeichert wird
void intToString(uint16_t number, char *buffer)
{
	uint16_t temp = number;
	if (number == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return;
	}
	
	uint16_t i = 0;
	
	while (temp > 0)
	{
		buffer[i++] = (temp % 10) + '0';
		temp /= 10;
	}
	
	buffer[i] = '\0';
	
	// String umdrehen
	uint8_t start = 0;
	uint8_t end = i - 1;
	char swap;
	
	while(start < end)
	{
		swap = buffer[start];
		buffer[start] = buffer[end];
		buffer[end] = swap;
		
		start++;
		end--;
	}
}

int main(void)
{
	lcd_init();
	lcd_backlight(true);
	lcd_clear();
	
	// Platz für "1000"
	char text[6];

	while (1)
	{
		for(uint16_t i = 0; i <= 1000; i++) 
		{
			lcd_clear();
			intToString(i, text);
			lcd_moveCursor(0,0);
			lcd_putString(text);
			
			_delay_ms(DELAY_MS);
		}
	}
}