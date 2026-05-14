/*
 * Praktikum4.c
 *
 * Created: 11/05/2026 16:56:18
 * Author : khush
 */ 

#include <avr/io.h>
#include "I2C_LCD.h"

int main(void)
{
	lcd_init();
	lcd_backlight(true);
	lcd_moveCursor(0,1);
	lcd_putString("Hello Display");

	while (1)
	{
	}
}