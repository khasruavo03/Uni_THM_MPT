/*
 * Praktikum7.c
 *
 * Created: 09/06/2026 18:43:13
 * Author : khush
 */ 

#include <avr/io.h>
#define F_CPU 4000000UL
#include <stdio.h>
#include <util/delay.h>
#include "I2C_LCD.h"

void adc0_init(void){
	ADC0.CTRLC = ADC_PRESC_DIV4_gc;
	VREF.ADC0REF = VREF_REFSEL_VDD_gc;
	ADC0.CTRLA = ADC_ENABLE_bm;
}

uint16_t adc0_read(uint8_t channel) {
	ADC0.MUXPOS = channel;
	ADC0.COMMAND = ADC_STCONV_bm;
	
	while(!(ADC0.INTFLAGS & ADC_RESRDY_bm));
	
	ADC0.INTFLAGS = ADC_RESRDY_bm;
	return ADC0.RES;
}

int main(void)
{
    /* Replace with your application code */
	char buffer [32];
	
	adc0_init();
	lcd_init();
	
    while (1) 
    {
		uint16_t adc = adc0_read(ADC_MUXPOS_AIN19_gc);
		// float voltage = adc * 3.3f / 1023.0f;
		int voltage = (adc * 3.3f / 4095.0f) * 10;
		float percent = (adc * 3.3f / 4095.0f)/ 3.3f * 100.0f;
		
		lcd_clear();
		// sprintf(buffer, "ADC=%u ", adc);
		// lcd_putString(buffer);
		sprintf(buffer, "U = %.1d.%dV", voltage/10, voltage % 10);
		lcd_putString(buffer);	
		lcd_moveCursor(0,1);
		sprintf(buffer, "%.0d%%", (int) percent);
		lcd_putString(buffer);
		
		_delay_ms(500);
    }
}

