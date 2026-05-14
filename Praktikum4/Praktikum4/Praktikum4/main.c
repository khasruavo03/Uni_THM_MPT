/*
 * Praktikum4.c
 *
 * Created: 11/05/2026 16:56:18
 * Author : khush
 */ 

#define F_CPU 24000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "I2C_LCD.h"

void display_int32_on_lcd(int32_t val);
void render_unsigned(uint32_t n);

// Button Definitionen auf PORT B
#define BTN_PLUS  (1 << 0)
#define BTN_MINUS (1 << 1)
#define BTN_MUL2  (1 << 2)
#define BTN_DIV2  (1 << 3)
#define ALL_BTNS  (0x0F)

enum state { WAIT_PRESS, WAIT_RELEASE };

// Hilfsfunktion zur Dezimalausgabe ohne sprintf (Vorgabe: Keine fertigen Funktionen)
void display_int32_on_lcd(int32_t val) {
	lcd_clear();
	_delay_ms(2); // Dem LCD Zeit geben, den Clear-Befehl zu verarbeiten
	
	if (val == 0) {
		lcd_putChar('0');
		} else {
		if (val < 0) {
			lcd_putChar('-');
			// Nutze uint32_t um den Überlauf bei -2147483648 zu verhindern
			uint32_t abs_val = (uint32_t)(-(val + 1)) + 1;
			render_unsigned(abs_val);
			} else {
			render_unsigned((uint32_t)val);
		}
	}
}

// Hilfsfunktion zum Zerlegen der Zahl in ASCII
void render_unsigned(uint32_t n) {
	char buffer[11];
	uint8_t i = 0;
	
	while (n > 0) {
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	
	// Rückwärts ausgeben
	while (i > 0) {
		lcd_putChar(buffer[--i]);
	}
}

int main(void) {
	int32_t currentNumber = 0;
	enum state currentState = WAIT_PRESS;

	// Initialisierung Hardware (I2C & LCD)
	// Die I2C_init() wird meist in der Library oder separat aufgerufen
	lcd_init();
	lcd_backlight(true);
	display_int32_on_lcd(currentNumber);

	// PORT B als Eingang für Buttons
	PORTB.DIRCLR = ALL_BTNS;
	// Pull-Ups aktivieren (Buttons schalten gegen GND)
	PORTB.PIN0CTRL = PORT_PULLUPEN_bm;
	PORTB.PIN1CTRL = PORT_PULLUPEN_bm;
	PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
	PORTB.PIN3CTRL = PORT_PULLUPEN_bm;

	while (1) {
		uint8_t input = PORTB.IN & ALL_BTNS;

		switch (currentState) {
			case WAIT_PRESS:
			// Wenn ein Pin 0 ist, wurde der Button gedrückt
			if (input != ALL_BTNS) {
				if (!(input & BTN_PLUS)) {
					currentNumber++;
				}
				else if (!(input & BTN_MINUS)) {
					currentNumber--;
				}
				else if (!(input & BTN_MUL2)) {
					// Effizient: Bitshift links
					currentNumber = currentNumber << 1;
				}
				else if (!(input & BTN_DIV2)) {
					// Effizient: Arithmetischer Bitshift rechts (erhält Vorzeichen)
					currentNumber = currentNumber >> 1;
				}

				display_int32_on_lcd(currentNumber);
				currentState = WAIT_RELEASE;
			}
			break;

			case WAIT_RELEASE:
			// Erst wenn alle Buttons wieder HIGH (1) sind
			if (input == ALL_BTNS) {
				_delay_ms(20); // Software-Entprellung
				currentState = WAIT_PRESS;
			}
			break;
		}
	}
}