#include <avr/io.h>

#define DELAY 20000

void delay()
{
    for(volatile long i=0;i<DELAY;i++);
}

int main()
{
    uint8_t counter = 0;

    PORTD.DIR = 0xFF;
    PORTC.DIR &= ~PIN4_bm;

    while(1)
    {
        if(PORTC.IN & PIN4_bm)
        {
            delay();

            if(PORTC.IN & PIN4_bm)
            {
                counter++;
                PORTD.OUT = counter;

                while(PORTC.IN & PIN4_bm);
            }
        }
    }
}