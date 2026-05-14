#include <avr/io.h>

#define DELAY_TIME 50000UL

void delay(void)
{
    for (volatile unsigned long i = 0; i < DELAY_TIME; i++)
    {
    }
}

int main(void)
{
    uint8_t led = 1;

    /* PD0–PD7 als Ausgang */
    PORTD.DIR = 0xFF;

    while (1)
    {

        /* links nach rechts */
        for (led = 1; led <= 0x80; led <<= 1)
        {
            PORTD.OUT = led;
            delay();
        }

        /* rechts nach links */
        for (led = 0x40; led >= 1; led >>= 1)
        {
            PORTD.OUT = led;
            delay();
        }

    }
}