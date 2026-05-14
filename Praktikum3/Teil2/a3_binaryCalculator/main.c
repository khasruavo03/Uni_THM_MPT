#include <avr/io.h>

#define DELAY 20000

void delay()
{
    for(volatile long i=0;i<DELAY;i++);
}

int main()
{
    uint8_t value = 0;

    PORTD.DIR = 0xFF;
    PORTC.DIR &= ~(PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);

    while(1)
    {
        uint8_t buttons = PORTC.IN & (PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);

        if(buttons)
        {
            delay();

            buttons = PORTC.IN & (PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);

            if(buttons == PIN4_bm)
                value++;

            else if(buttons == PIN5_bm)
                value--;

            else if(buttons == PIN6_bm)
                value <<= 1;

            else if(buttons == PIN7_bm)
                value >>= 1;

            PORTD.OUT = value;

            while(PORTC.IN & (PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm));
        }
    }
}