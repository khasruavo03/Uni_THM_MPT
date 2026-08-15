/*
 * Bonus.c
 *
 * Created: 04/07/2026 11:18:09
 * Author : khush
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "song.h"

#define SINE_TABLE_SIZE (sizeof(sine_table) / sizeof(sine_table[0]))

void dac_init(void) 
{
	VREF.DAC0REF = VREF_REFSEL_2V048_gc; 
	
	// Korrektur: Daten richtig im Register schreiben 
	// Um 6 shiften bei DATAL
	uint16_t value = 512;
	DAC0.DATAL = (value & 0x03) << 6;
	DAC0.DATAH = value >> 2;
	DAC0.CTRLA = DAC_OUTEN_bm | DAC_ENABLE_bm;
}

void timer_init(void)
{
	PORTD.DIRSET = PIN6_bm;

	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV4_gc | TCA_SINGLE_ENABLE_bm;
}

void play_notes(uint16_t f)  
{
	TCA0.SINGLE.PER = (1000000UL / (f * SINE_TABLE_SIZE)) -1;
}

volatile uint16_t i = 0; // Index der Sinustabelle


int main(void)
{
    /* Replace with your application code */
	dac_init();
	timer_init();
	
	play_notes(h1); // Ton a1
	
	sei();
    while (1) 
    {
    }
}

ISR(TCA0_OVF_vect) 
{
	uint16_t value = sine_table[i];
	DAC0.DATAL = (value & 0x03) << 6;
	DAC0.DATAH = value >> 2;
	
	i++;
	if(i >= SINE_TABLE_SIZE)
	{
		i = 0;
	}
	
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}
