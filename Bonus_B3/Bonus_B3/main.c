/*
 * Bonus_B3.c
 *
 * Created: 05/07/2026 21:38:43
 * Author : khush
 */ 

#include <avr/io.h>


#include <avr/io.h>
#include <avr/interrupt.h>
#include "song.h"

#define F_CPU 4000000UL

#define SINE_TABLE_SIZE (sizeof(sine_table) / sizeof(sine_table[0]))
#define TAKT ((F_CPU / (4)))

volatile uint16_t i = 0; // Index der Sinustabelle
volatile double volume = 255.0; // Lautstärke
uint32_t ms_ticks = 0; //Tick-Zähler

void dac_init(void)
{
	VREF.DAC0REF = VREF_REFSEL_2V048_gc;
	
	// Korrektur: Daten richtig im Register schreiben
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

void play_song (const song *s) {
	for(uint16_t n = 0; n < s->length; n++)
	{
		/* if (n > 0 && s->tone[n] == s->tone[n-1])
		{
			volume = 255;
		} else {
			volume = 255;
		} */
		
		// play_notes(s->tone[n]);
		
		// Beat = 60/ bpm -> s Beat = 60000 / bpm -> in ms
		uint32_t beat = 60000UL / s->bpm;
		
		// Notendauer in ms
		uint32_t note_ms = beat / s->tone_length[n];
		
		volume = 1.0;
		
		// Lautstärke schrittweise reduzieren
		uint32_t start = ms_ticks;
		
		while((ms_ticks - start) < note_ms)
		{
			// KEIN DELAY!!!!!
			
			// _delay_ms(10);
			if(volume > 0.05)
			{
				volume -= 0.05;
			}
		}
		
		play_notes(s->tone[n]);
		
	}
}

int main(void)
{
	/* Replace with your application code */
	dac_init();
	timer_init();
	sei();
	
	
	while (1)
	{
		play_song(&mario);
	}
}

ISR(TCA0_OVF_vect)
{
	uint16_t value = sine_table[i];
	value = (uint16_t) (value * volume);
	DAC0.DATAL = (value & 0x03) << 6;
	DAC0.DATAH = value >> 2;
	
	i++;
	if(i >= SINE_TABLE_SIZE)
	{
		i = 0;
	}
	
	ms_ticks++;
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}


