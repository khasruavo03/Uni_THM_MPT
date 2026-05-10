/**
 * @file main.c
 * @author khush
 * @date 2026-05-04
 * @brief Main function
 */
#include <avr/io.h>

// Aufgabe 3.1
int main(){
    PORTD.DIR |= PIN7_bm; // Set pin 7 of PORTD as output
    PORTD.OUT |= PIN7_bm;
    // Add your code here and press Ctrl + Shift + B to build

    return 0;
} 