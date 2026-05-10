/**
 * @file main.c
 * @author khush
 * @date 2026-05-10
 * @brief Main function
 */

 #include <avr/io.h>
 /* #define PIN7_bm (1 << 7) // Bit mask for pin 7 */

void setup() {
    PORTD.DIR |= PIN7_bm; // Set pin 7 of PORTD as output
    PORTD.OUT |= PIN7_bm; // Set pin 7 of PORTD to high
}

void loop() {
    // Add your code here and press Ctrl + Shift + B to build
    // This function will run repeatedly after setup() is called once.
}

/* // Aufgabe 3.1
int main(){
    PORTD.DIR |= PIN7_bm; // Set pin 7 of PORTD as output
    PORTD.OUT |= PIN7_bm;
    // Add your code here and press Ctrl + Shift + B to build

    return 0;
}  */
