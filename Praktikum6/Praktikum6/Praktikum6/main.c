/*
 * Praktikum6.c
 *
 * Created: 01/06/2026 15:20:46
 * Author : khush
 */ 

#include <avr/io.h>

#define F_CPU 4000000UL

#include <avr/interrupt.h>

// PWM als Software-PWM per Timer erzeugt

#define SERVO_LEFT    250   // 1.0 ms
#define SERVO_CENTER  375   // 1.5 ms
#define SERVO_RIGHT   500   // 2.0 ms

#define SERVO_PERIOD 5000 //20ms Periode

// Fehler, das Software-Zähler innerhalb eines Interrupts: volatile uint16_t counter = 0;
volatile uint16_t pulseWidth = 150;
volatile int16_t direction = 1;

void tca_config(void) {
	PORTF.DIRSET = PIN4_bm;
	
	TCA0.SINGLE.PER = SERVO_PERIOD;
	TCA0.SINGLE.CMP0 = pulseWidth;

	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm | TCA_SINGLE_CMP0_bm;

	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV16_gc | TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_OVF_vect) {
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
	PORTF.OUTSET = PIN4_bm;
	TCA0.SINGLE.CMP0 = pulseWidth;
	pulseWidth += direction;
	if(pulseWidth >= SERVO_RIGHT) {
		direction = -1;
	}
	if(pulseWidth <= SERVO_LEFT) {
		direction = 1;
	}
	/* Fehler 
	*
	* counter++;
	*
	* if (counter == 1) {
	* 	PORTF.OUTSET = PIN4_bm;
	* }
	*
	* if (counter == pulseWidth) {
	* 	PORTF.OUTCLR = PIN4_bm;
	* }
	*
	* if(counter >= 2000) {
	* 	counter = 0;
	* } */
}

ISR(TCA0_CMP0_vect)
{
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm;
	PORTF.OUTCLR = PIN4_bm;
}

int main(void)
{
    /* Replace with your application code */
	tca_config();
	
	sei();
	
	while(1)
	{
		// Fehler!
		/* for(uint16_t p = SERVO_LEFT; p <= SERVO_RIGHT; p++)
		* {
		*	pulseWidth = p;
		*
		* for(volatile uint32_t d = 0; d < 10000; d++);
		* }
		*
		* for(int16_t p = SERVO_RIGHT; p >= SERVO_LEFT; p--)
		* {
		*
		* for(volatile uint32_t d = 0; d < 10000; d++);
		* }
		*/
	}
}

