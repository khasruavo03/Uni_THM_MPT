/**
 * @file main.c
 * @author khush
 * @date 2026-05-07
 * @brief Main function
 */
#include <avr/io.h>

// Aufgabe 3.2
#define LED1_PIN PIN7_bm
#define LED2_PIN PIN6_bm

// Blinkgeschwindigkeit
#define DELAY_COUNT 50000UL

void delay(void) 
{
    // Frage 1
    // Erzeugt eine Zeitverzögerung --> Busy Waiting
    // Der Prozessor führt eine leere Schleife aus, die nur Zeit verbraucht
    // Während dieser Zeit macht der Controller nichts anders

    // Frage 2
    // volatile ist ein Typqualifizier wie const oder static
    // Er sagt den Compiler, dass der Wert dieser Variable sich jederzeit außerhalb des Programmcodes ändern kann
    // Deshalb darf der Compiler keine Optimierung durchführen, die den Zugriff auf diese Variable reduzieren
    // Ohne volatile könnte der Compiler die Schleife optimieren, indem er sie entfernt oder durch eine konstante Zeit ersetzt, da er denkt, dass sie keinen Effekt hat
    for (volatile unsigned long i = 0; i < DELAY_COUNT; i++)
    {
        // Delay Loop
    }
}

// Frage 3
// Am besten das Toogle Register, da es das entsprechende Bit automatisch invertiert (Toggle)
// Somit kann man eine LED sehr ein- und ausschalten, ohne den aktuellen Zustand prüfen zu müssen
int main() 
{
    // LED Konfigurieren
    // PD7 als Ausgang setzen
    PORTD.DIR |= LED1 | LED2;

    while (1)
    {
        /* // LED einschalten
        PORTD.OUT |= LED_PIN;
        delay();

        // LED ausschalten
        PORTD.OUT &= ~LED_PIN;
        delay(); */

        // Erweiterung des Programms

        // Zwei LEDs abwechselend blinken

        // LED1 an, LED2 aus
        PORTD.OUTSET = LED1;
        PORTD.OUTCLR = LED2;
        delay();
        // LED1 aus, LED2 an
        PORTD.OUTCLR = LED1;
        PORTD.OUTSET = LED2;
        delay();
    }

}
