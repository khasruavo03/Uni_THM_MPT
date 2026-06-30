/*
 * Praktikum8.c
 *
 * Created: 20/06/2026 10:28:35
 * Author : khush
 */ 

/*
 * Praktikum8.c
 *
 * Created: 20/06/2026
 */

#include <avr/io.h>

#define F_CPU 4000000UL
#include <util/delay.h>

#include <stdio.h>
#include "I2C_LCD.h"
#include "AVR128DB48_I2C.h"

#define TCS34725_ADDR 0x29

char text[17];

// Register
#define ENABLE 0x00
#define CDATAL 0x14
#define CDATAH 0x15
#define RDATAL 0x16
#define RDATAH 0x17
#define GDATAL 0x18
#define GDATAH 0x19
#define BDATAL 0x1A
#define BDATAH 0x1B


// Register schreiben

void tcs_writeReg(uint8_t reg, uint8_t value)
{
    uint8_t data[2];

    data[0] = 0x80 | reg;     // Command-Bit setzen
    data[1] = value;

    i2c_write(TCS34725_ADDR, data, 2);
}

// 16-Bit Register lesen
uint16_t tcs_read16(uint8_t reg)
{
    uint8_t cmd;
    uint8_t data[2];

    cmd = 0x80 | reg;

    i2c_write(TCS34725_ADDR, &cmd, 1);
    i2c_read(TCS34725_ADDR, data, 2);

    return ((uint16_t)data[1] << 8) | data[0];
}

// Sensor initialisieren
void tcs_init(void)
{

    tcs_writeReg(ENABLE, 0x03);   // PON + AEN
    _delay_ms(50);
}

int main(void)
{
    uint16_t r, g, b, c;

    i2c_init();

    lcd_init();
    lcd_backlight(true);
    lcd_clear();

    tcs_init();

    while (1)
    {
        r = tcs_read16(RDATAL);
        g = tcs_read16(GDATAL);
        b = tcs_read16(BDATAL);
		c = tcs_read16(CDATAL);

        // LCD ist nur 16 Zeichen breit.
        // Deshalb Werte auf 0..255 skalieren
        r >>= 8;
        g >>= 8;
        b >>= 8;
		// c >>= 8;

        lcd_moveCursor(0,0);
        sprintf(text, "rgb:%3u,%3u,%3u", r, g, b);
        lcd_putString(text);

        /* lcd_moveCursor(0,1);
        sprintf(text, "c:%5u", c);
        lcd_putString(text); */

        _delay_ms(100);
    }
}