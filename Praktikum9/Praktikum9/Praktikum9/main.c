/*
 * Praktikum9.c
 *
 * Created: 24/06/2026 14:04:48
 * Author : khush
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

volatile uint8_t cmdReady = 0;
volatile uint8_t cmd = 0;

volatile uint16_t lastTime = 0;
volatile uint16_t pulseWidth = 0;

void GPIO_init(void)
{
	PORTD.DIRCLR = PIN2_bm; // PD2 = IR-Eingang
	PORTD.PIN2CTRL = PORT_PULLUPEN_bm;
	PORTD.DIRSET = PIN0_bm;
}

void timer_init(void)
{
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
	TCA0.SINGLE.CNT = 0;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc | TCA_SINGLE_ENABLE_bm;
}

void interrupt_init(void)
{
	PORTD.PIN2CTRL |= PORT_ISC_BOTHEDGES_gc;
}

ISR(PORTD_PORT_vect)
{
	uint16_t now = TCA0.SINGLE.CNT;

	pulseWidth = now - lastTime;
	lastTime = now;

	// Hier pulseWidth auswerten
	if (cmdReady)
	{
		cmdReady = 0;

		switch(cmd)
		{
			case 0x07:      // Taste 0
			// Timer = Timer*10 + 0;
			break;

			case 0x16:      // Taste 1
			break;

			case 0x46:      // UP
			break;

			case 0x15:      // DOWN
			break;

			case 0x40:      // X
			break;
		}
	}

	PORTD.INTFLAGS = PIN2_bm;      // Interrupt löschen
}

int main(void)
{
    GPIO_init();
	timer_init();
	interrupt_init();
    
    sei();   

    while (1)
    {
    }
}

