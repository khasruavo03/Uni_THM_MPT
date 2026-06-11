/*
 * Praktikum6.c
 *
 * Created: 01/06/2026 15:20:46
 * Author : khush
 */ 

#include <avr/io.h>

#define F_CPU 4000000UL

int main(void)
{
    /* Replace with your application code */
	PORTD.DIRSET = PIN0_bm;
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTD_gc;
	TCA0.SINGLE.PER = 999;
	TCA0.SINGLE.CMP0 = 250;
	TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc | TCA_SINGLE_ENABLE_bm;
    while (1) 
    {
    }
}

