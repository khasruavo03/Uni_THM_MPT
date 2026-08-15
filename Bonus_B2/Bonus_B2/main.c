/*
 * Bonus_B2.c
 *
 * Created: 05/07/2026 20:23:14
 * Author : khush
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "song.h"

#define SINE_TABLE_SIZE (sizeof(sine_table) / sizeof(sine_table[0]))

volatile uint16_t i = 0; // Index der Sinustabelle
volatile uint16_t current_freq = 0;

void dac_init(void)
{
	VREF.DAC0REF = VREF_REFSEL_2V048_gc;
	uint16_t value = 512;
	DAC0.DATAL = value & 0x03;
	DAC0.DATAH = value >> 2;
	DAC0.CTRLA = DAC_OUTEN_bm | DAC_ENABLE_bm;
}

void button_init(void) {
	PORTA.DIRCLR = PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm ;
	PORTB.DIRCLR = PIN0_bm;
	PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
	PORTA.PIN3CTRL = PORT_PULLUPEN_bm;
	PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
	PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
	PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
	PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
	PORTB.PIN0CTRL = PORT_PULLUPEN_bm;
}

void timer_init(void)
{
	PORTD.DIRSET = PIN6_bm;

	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc | TCA_SINGLE_ENABLE_bm;
}

void play_speaker(void) {
		if(current_freq == 0)
		{
			uint16_t value = 512;      // Mittelwert = ruhig
			DAC0.DATAL = value & 0x03;
			DAC0.DATAH = value >> 2;
		}
	uint16_t value = sine_table[i];
	DAC0.DATAL = value & 0x03;
	DAC0.DATAH = value >> 2;
}

void play_notes(uint16_t f)
{
	if (f == 0) {
		return;
	}
	TCA0.SINGLE.PER = (100000UL / (f * SINE_TABLE_SIZE)) -1;
}


int main(void)
{
	/* Replace with your application code */
	dac_init();
	button_init();
	timer_init();
	
	
	
	sei();
	
	while (1)
		{
			if(!(PORTA.IN & PIN2_bm))
			current_freq = c;
			else if(!(PORTA.IN & PIN3_bm))
			current_freq = d;
			else if(!(PORTA.IN & PIN4_bm))
			current_freq = e;
			else if(!(PORTA.IN & PIN5_bm))
			current_freq = f;
			else if(!(PORTA.IN & PIN6_bm))
			current_freq = g;
			else if(!(PORTA.IN & PIN7_bm))
			current_freq = h;
			else if(!(PORTB.IN & PIN0_bm))
			current_freq = a;
			else
			current_freq = 0;
			play_notes(current_freq);
	}
}

ISR(TCA0_OVF_vect)
{	
	if(current_freq == 0)
	{
		uint16_t value = 512;      // Mittelwert = ruhig
		DAC0.DATAL = value & 0x03;
		DAC0.DATAH = value >> 2;
	} else {
		play_speaker();
		i++;
		if(i >= SINE_TABLE_SIZE)
		{
			i = 0;
		}
	}
	
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}