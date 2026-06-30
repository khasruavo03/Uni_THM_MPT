/*
 * Praktikum7.c
 *
 * Created: 09/06/2026 18:43:13
 * Author : khush
 */ 

#include <avr/io.h>
#define F_CPU 4000000UL
#include <avr/interrupt.h>
#include "I2C_LCD.h"

#define BAUD_RATE 9600

#include <stdio.h>

char buffer[30];
uint8_t r,g,b;


void usart0_init(void) {
	uint16_t baud = (uint16_t) (64.0 * F_CPU) / (16.0 * BAUD_RATE);
	
	USART0.BAUD = baud;
	USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
	USART0.CTRLC = USART_CHSIZE_8BIT_gc;
}

void pwm_init(void) {
	PORTE.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm;
	PORTMUX.TCAROUTEA = PORTMUX_TCA0_PORTE_gc;
	TCA0.SINGLE.PER = 255;
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | 
						TCA_SINGLE_CMP0EN_bm | 
						TCA_SINGLE_CMP1EN_bm | 
						TCA_SINGLE_CMP2EN_bm;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc | TCA_SINGLE_ENABLE_bm;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
	TCA0.SINGLE.CMP0 = r;
	TCA0.SINGLE.CMP1 = g;
	TCA0.SINGLE.CMP2 = b;
}


char usart0_readchar(void) {
	while(!(USART0.STATUS & USART_RXCIF_bm));
	return USART0.RXDATAL;
}

void readline(char *buffer)
{
	uint8_t i = 0;
	char c;
	while(1)
	{
		c = usart0_readchar();
		if(c == '\r' || c == '\n')
		{
			buffer[i] = '\0';
			break;
		}

		buffer[i++] = c;
	}
}


int main(void)
{
	usart0_init();
	pwm_init();
	
	set_rgb(255,0,0);

	while(1)
	{
		readline(buffer);

		if(sscanf(buffer,"%hhu,%hhu,%hhu",&r,&g,&b) == 3)
		{
			if(r > 255) r = 255;
			if(g > 255) g = 255;
			if(b > 255) b = 255;

			set_rgb(r,g,b);
		}
	}
}

