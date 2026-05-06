// Aufgabe 1

#include <stdio.h>
#include <string.h>

int main(void) {
    char str[] = "Hello World as String (char array)";
    for (int i = 0, len = strlen(str); i < len; i++) {
        printf("%c", str[i]);
    }
    printf("\n");
    return 0;
}

// Aufgabe 1.2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    int len = 26;

    // Dynamische Speicherallokation
    char *alphabet = (char *)malloc((len + 1) * sizeof(char));

    for(int i=0; i < len; i++) {
        *(alphabet + i) = (char) ('A' + i);
    }
    *(alphabet + len) = '\0';

    for(int i=0; i < len; i+=2) {
        printf("Geben Sie den %c. Buchstaben ein: ", *(alphabet + i));
    }
    printf("\n");

    free(alphabet);

    return 0;
}

// Aufgabe 1.3
#include <stdint.h>
#include <stdio.h>

#define MAX_STRLEN 11 

// Teil 1
uint16_t set_bit(uint16_t number, uint8_t position) {
    return number | ((uint16_t)1 << position);
}

// Teil 2
uint16_t swap_bytes(uint16_t number) {
    return (uint16_t)((number >> 8) | (number << 8));
}

// Teil 3
uint8_t get_high_nibble(uint8_t number) {
    return (uint8_t)((number >> 4) & 0x0F);
}

// Aufgabe 1.4
char uint32_str[MAX_STRLEN];

void uint32_to_string(uint32_t num) {
    int i = 0;

    if (num == 0) {
        uint32_str[i++] = '0';
        uint32_str[i] = '\0';
        return;
    }

    while (num > 0) {
        uint32_t digit = num % 10;
        uint32_str[i++] = (char) (digit + '0');
        num /= 10;
    }
    uint32_str[i] = '\0';

    int start = 0;
    int end = i - 1;
    
    while (start < end) {
        char temp = uint32_str[start];
        uint32_str[start] = temp;
        start++;
        end--;
    }
}

int main(void) {
    uint32_t num = 4294967295U;
    uint32_to_string(num);
    printf("Zahl als String: %s\n", uint32_str);
    return 0;
}