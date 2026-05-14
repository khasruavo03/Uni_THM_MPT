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
    uint8_t counter = 0;

    /* PD0–PD7 als Ausgang */
    PORTD.DIR = 0xFF;

    while (1)
    {
        PORTD.OUT = counter;  // binären Wert anzeigen
        delay();

        counter++;            // nächste Zahl
    }
}