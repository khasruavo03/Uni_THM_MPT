#include <avr/io.h>

/* 
// Teil A
int main()
{
    PORTD.DIR |= PIN0_bm;   // LED PD0 Output
    PORTC.DIR &= ~PIN4_bm;  // PC4 Input

    while(1)
    {
        if(PORTC.IN & PIN4_bm)
            PORTD.OUT |= PIN0_bm;
        else
            PORTD.OUT &= ~PIN0_bm;
    }
} 
    */

// Teil B

int main()
{
    PORTD.DIR = 0xFF; // alle LEDs Output
    PORTC.DIR &= ~(PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);

    while(1)
    {
        if(PORTC.IN & (PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm))
            PORTD.OUT = 0xFF;
        else
            PORTD.OUT = 0x00;
    }
}