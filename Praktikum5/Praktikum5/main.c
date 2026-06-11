/*
 * Praktikum5.c
 *
 * Created: 23/05/2026 10:23:02
 * Author : khush
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <I2C_LCD.h>

/*
I2C_LCD.h

i2c_status lcd_init(void);
i2c_status lcd_enable(bool enable);
i2c_status lcd_clear(void);
i2c_status lcd_moveCursor(uint8_t x, uint8_t y);
i2c_status lcd_backlight(bool enable);
i2c_status lcd_putChar(char character);
i2c_status lcd_putString(char* string);
i2c_status lcd_leftToRight(void);
i2c_status lcd_rightToLeft(void);
*/

/*
Aufgabe 01

// Damit die Variable (mit volatile) nicht 
// falsch optimiert wird vom Compiler
// Weil die Variable in der ISR ver�ndert wird, 
// und au�erhalb gelesen werden k�nnte 
volatile uint8_t led_on = 0;
volatile uint32_t rng_state = 123456789;

// Z�hler f�r vergangene Sekunden
volatile uint32_t seconds = 0;

// LCD muss aktualisiert werden
volatile uint8_t update_display = 0;

// mathematischer Algorithmus
uint32_t xorshift32(void)
{
	uint32_t x = rng_state;
	
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	
	rng_state = x;
	return x;
}

// Farbe erzeugen
void set_rgb(uint8_t color) {
	PORTE.OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm;
	
	if (color & 0x01){
		PORTE.OUTSET = PIN0_bm;
	}
	
	if (color & 0x02) {
		PORTE.OUTSET = PIN1_bm;
	}
	
	if (color & 0x04) {
		PORTE.OUTSET = PIN2_bm;
	}
}

ISR(PORTC_PORT_vect) {
	if (PORTC.INTFLAGS & PIN4_bm) {
		led_on = !led_on;
		if (led_on) {
			uint8_t color;
			do 
			 {
				 color = xorshift32() & 0x07;
			 }
			 while (color == 0);
			 
			 set_rgb(color);
		} else {
			PORTE.OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm;
		}
		
		PORTC.INTFLAGS = PIN4_bm;
	}
}
*/

/*
// Aufgabe 02
void timer_init(void) {
	TCA0.SINGLE.CTRLA = 0;
	TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_NORMAL_gc;
	TCA0.SINGLE.PER = 3906;
	TCA0.SINGLE.INTCTRL = TCA_SINGLE_OVF_bm;
	TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1024_gc | TCA_SINGLE_ENABLE_bm;
}
*/

/* // Augabe 03
typedef enum
{
	RED,
	RED_YELLOW,
	GREEN,
	YELLOW
} traffic_state_t;

volatile traffic_state_t state = RED;
volatile uint8_t transition_active = 0;
volatile uint8_t timer_seconds = 0;

void set_rgb(uint8_t color)
{
	PORTE.OUTCLR =
	PIN0_bm |
	PIN1_bm |
	PIN2_bm;

	if(color & 0x01)
	PORTE.OUTSET = PIN0_bm;

	if(color & 0x02)
	PORTE.OUTSET = PIN1_bm;

	if(color & 0x04)
	PORTE.OUTSET = PIN2_bm;
}

void timer_init(void)
{
	TCA0.SINGLE.CTRLA = 0;

	TCA0.SINGLE.CTRLB =
	TCA_SINGLE_WGMODE_NORMAL_gc;

	TCA0.SINGLE.PER = 3906;

	TCA0.SINGLE.INTCTRL =
	TCA_SINGLE_OVF_bm;

	TCA0.SINGLE.CTRLA =
	TCA_SINGLE_CLKSEL_DIV1024_gc |
	TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_OVF_vect)
{
	timer_seconds++;

	if(state == RED_YELLOW)
	{
		if(timer_seconds >= 1)
		{
			state = GREEN;

			set_rgb(0x02);

			transition_active = 0;

			timer_seconds = 0;
		}
	}

	else if(state == YELLOW)
	{
		if(timer_seconds >= 1)
		{
			state = RED;

			set_rgb(0x01);

			transition_active = 0;

			timer_seconds = 0;
		}
	}

	TCA0.SINGLE.INTFLAGS =
	TCA_SINGLE_OVF_bm;
}

ISR(PORTC_PORT_vect)
{
    // Button PC4
    //ROT -> ROT_GELB

    if(PORTC.INTFLAGS & PIN4_bm)
    {
        if(state == RED &&
           !transition_active)
        {
            state = RED_YELLOW;

            set_rgb(0x03);

            transition_active = 1;

            timer_seconds = 0;
        }

        PORTC.INTFLAGS = PIN4_bm;
    }

    // Button PC5
    // GRUEN -> GELB

    if(PORTC.INTFLAGS & PIN5_bm)
    {
        if(state == GREEN &&
           !transition_active)
        {
            state = YELLOW;

            set_rgb(0x03);

            transition_active = 1;

            timer_seconds = 0;
        }

        PORTC.INTFLAGS = PIN5_bm;
    }
}
*/

// Aufgabe 04
volatile uint32_t remaining_seconds = 0;
volatile uint8_t timer_running = 0;
volatile uint8_t update_display = 1;
volatile uint8_t timer_finished = 0;

void set_rgb(uint8_t color)
{
	PORTE.OUTCLR =
	PIN0_bm |
	PIN1_bm |
	PIN2_bm;

	if(color & 0x01)
	PORTE.OUTSET = PIN0_bm;

	if(color & 0x02)
	PORTE.OUTSET = PIN1_bm;

	if(color & 0x04)
	PORTE.OUTSET = PIN2_bm;
}

void timer_init(void)
{
	TCA0.SINGLE.CTRLA = 0;

	TCA0.SINGLE.CTRLB =
	TCA_SINGLE_WGMODE_NORMAL_gc;

	TCA0.SINGLE.PER = 3906;

	TCA0.SINGLE.INTCTRL =
	TCA_SINGLE_OVF_bm;

	TCA0.SINGLE.CTRLA =
	TCA_SINGLE_CLKSEL_DIV1024_gc |
	TCA_SINGLE_ENABLE_bm;
}

ISR(TCA0_OVF_vect)
{
	if(timer_running)
	{
		if(remaining_seconds > 0)
		{
			remaining_seconds--;
			update_display = 1;
			if(remaining_seconds == 0)
			{
				timer_running = 0;
				timer_finished = 1;
			}
		}
	}
	TCA0.SINGLE.INTFLAGS =
	TCA_SINGLE_OVF_bm;
}

ISR(PORTC_PORT_vect)
{
    // PC4
    // +5 Sekunden
    if(PORTC.INTFLAGS & PIN4_bm)
    {
        remaining_seconds += 5;
        update_display = 1;
        PORTC.INTFLAGS = PIN4_bm;
    }

    // PC5
    // Start / Pause
    if(PORTC.INTFLAGS & PIN5_bm)
    {
        timer_running = !timer_running;
        PORTC.INTFLAGS = PIN5_bm;
    }
}

int main(void) {
	
	/*
	// Aufgabe 01
	// RGB-LED Pins als Output
    PORTE.DIRSET = PIN0_bm | PIN1_bm | PIN2_bm;
	
	// LED ausschalten
	PORTE.OUTCLR = PIN0_bm | PIN1_bm | PIN2_bm;
	
	// Button als Input
	PORTC.DIRCLR = PIN4_bm;
	
	// Pullup aktiviert haben und Interrupt ausl�sen
	PORTC.PIN4CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;
	*/
	
	/* // Aufgabe 02
	
	char buffer[16];

    lcd_init();
    lcd_enable(true);
    lcd_backlight(true);
    lcd_clear();

    timer_init();
	*/
	
	/* 
	// Aufgabe 03
	PORTE.DIRSET =
	PIN0_bm |
	PIN1_bm |
	PIN2_bm;

	set_rgb(0x01);
	
	PORTC.DIRCLR =
	PIN4_bm |
	PIN5_bm;

	PORTC.PIN4CTRL =
	PORT_PULLUPEN_bm |
	PORT_ISC_FALLING_gc;

	PORTC.PIN5CTRL =
	PORT_PULLUPEN_bm |
	PORT_ISC_FALLING_gc;
	
	timer_init(); */
	
	// Aufgabe 04
	    char buffer[16];

    // RGB LED

    PORTE.DIRSET =
        PIN0_bm |
        PIN1_bm |
        PIN2_bm;

    PORTE.OUTCLR =
        PIN0_bm |
        PIN1_bm |
        PIN2_bm;
	
	// Buttons
	PORTC.DIRCLR =
	PIN4_bm |
	PIN5_bm;

	PORTC.PIN4CTRL =
	PORT_PULLUPEN_bm |
	PORT_ISC_FALLING_gc;

	PORTC.PIN5CTRL =
	PORT_PULLUPEN_bm |
	PORT_ISC_FALLING_gc;
	
	// LCD
	lcd_init();
    lcd_enable(true);
    lcd_backlight(true);
    lcd_clear();

    timer_init();
	
	// Interrupts global aktivieren
	sei();
	
    while (1) 
    {
		/*
		// AUfgabe 02
		// LCD nur aktualisieren, wenn ISR dies signalisiert
        if(update_display)
        {
            update_display = 0;

            // Zahl -> String
            snprintf(buffer,
                     sizeof(buffer),
                     "%lu",
                     seconds);

            lcd_clear();
			lcd_moveCursor(0,0);
            lcd_putString(buffer);
        }
		*/
		
		// Aufgabe 04
		// LCD aktualisieren
        if(update_display)
        {
            update_display = 0;
            snprintf(buffer,
                     sizeof(buffer),
                     "%lu",
                     remaining_seconds);
            lcd_clear();
            lcd_moveCursor(0,0);
			lcd_putString(buffer);
        }

        if(timer_finished)
        {
            timer_finished = 0;

            //Rot einschalten
            set_rgb(0x01);
        }
    }
}

