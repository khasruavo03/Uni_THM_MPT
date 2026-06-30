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

void usart0_init(void) {
	uint16_t baud = (uint16_t) (64.0 * F_CPU) / (16.0 * BAUD_RATE);
	
	USART0.BAUD = baud;
	USART0.CTRLB = USART_TXEN_bm | USART_RXEN_bm;
}

void usart0_sendChar(char c)
{
	while (!(USART0.STATUS & USART_DREIF_bm));
	USART0.TXDATAL = c;
}

void usart0_sendString(char *str)
{
	while(*str) {
		usart0_sendChar(*str++);
	}
}

void buttons_init(void)
{
	PORTC.DIRCLR =
	PIN4_bm |
	PIN5_bm |
	PIN6_bm |
	PIN7_bm;

	PORTC.PIN4CTRL =
	PORT_PULLUPEN_bm |
	PORT_ISC_FALLING_gc;

	PORTC.PIN5CTRL =
	PORT_PULLUPEN_bm |
	PORT_ISC_FALLING_gc;

	PORTC.PIN6CTRL =
	PORT_PULLUPEN_bm |
	PORT_ISC_FALLING_gc;

	PORTC.PIN7CTRL =
	PORT_PULLUPEN_bm |
	PORT_ISC_FALLING_gc;
}

ISR(PORTC_PORT_vect)
{
	uint8_t flags = PORTC.INTFLAGS;

	if(flags & PIN4_bm)
	{
		usart0_sendString("Button C4 gedrückt\r\n");
	}

	if(flags & PIN5_bm)
	{
		usart0_sendString("Button C5 gedrückt\r\n");
	}

	if(flags & PIN6_bm)
	{
		usart0_sendString("Button C6 gedrückt\r\n");
	}

	if(flags & PIN7_bm)
	{
		usart0_sendString("Button C7 gedrückt\r\n");
	}

	PORTC.INTFLAGS = flags;
}


int main(void)
{
     usart0_init();

     buttons_init();

     sei();

     usart0_sendString("USART gestartet\r\n");

     while(1)
     {

     }
}

