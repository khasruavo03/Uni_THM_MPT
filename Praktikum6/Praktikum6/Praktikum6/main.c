/*
 * Praktikum6.c
 *
 * Created: 01/06/2026 15:20:46
 * Author : khush
 */ 

#include <avr/io.h>

#define F_CPU 4000000UL

#include <avr/interrupt.h>

#define SERVO_LEFT    100   // 1.0 ms
#define SERVO_CENTER  150   // 1.5 ms
#define SERVO_RIGHT   200   // 2.0 ms

volatile uint16_t counter = 0;
volatile uint16_t pulseWidth = 150;

ISR(TCA0_OVF_vect) {
	TCA0.INTFLAGS = TCA0_OVF_vect;
	// PORTF.OUTCLR = PIN4_bm;
	
	counter++;
	
	if (counter == 1) {
		PORTF.OUTSET = PIN4_bm;
	}
	
	if (counter == pulseWidth) {
		PORTF.OUTCLR = PIN4_bm;
	}
	
	if(counter >= 2000) {
		counter = 0;
	}
}

int main(void)
{
    /* Replace with your application code */
	PORTF.DIRSET = PIN4_bm;
	
	// TCA0.SINGLE.CCMP = 40;
	// TCA0.SINGLE.CTRLB = TCA_CNTMODE_INT_gc;
	
	// TCA0.INTCTRL = TCA_CAPT_bm;
	TCA0.SINGLE.PER = 20000;
	// TCA Datasheet
	// TCA Overflow -> Verwendung um die Richtungslogik ISR (Fallunterschiedung zum Situationen 1ms, 1.5ms, 2ms)
	// Jedes mal schauen ob das Compare-Register welche Richtung
	// TCA Compare -> Compare-Register zurücksetzen
	// PWM Intialisiert
	// Beachten wie Timer konfiguriert ist => Sinvoll Prescaler zu verwenden
	// Aurechnen wie viel Takt zu verwenden
	
	
	
	// TCA0.CTRLA = TCA_CLKSEL_DIV1_gc | TCA_ENABLE_bm;
	
	sei();
	
	
	
	while(1)
	{
		// Fehler!
		// Über Timer läuft => Overflow-Interrupt
		// Toggeln ob Signal High oder Low
		// Bis zur Compare-Register erreicht ist
		for(uint16_t p = SERVO_LEFT; p <= SERVO_RIGHT; p++)
		{
			pulseWidth = p;

			for(volatile uint32_t d = 0; d < 10000; d++);
		}

		for(int16_t p = SERVO_RIGHT; p >= SERVO_LEFT; p--)
		{
			pulseWidth = p;

			for(volatile uint32_t d = 0; d < 10000; d++);
		}
	}
}

