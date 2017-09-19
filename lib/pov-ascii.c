// ------- Preamble -------- //
#include <avr/io.h>     // for the pin definitions
#include <string.h>     // for string operations like strlen
#include <util/delay.h> // for the delay function

#include "m38_font.h" // for the font

#include "pov-ascii.h"

// -------- Constants --------- //

/* the delay time waited between the flashing of the LEDs
 * I had good results with about 5ms to 10ms */
const int delay_time = 6;

/* length of the font representation/array of the character */
const int character_length = sizeof(font[0]) / sizeof(font[0][0]);


// -------- Functions --------- //
void flash(uint8_t times) {
    for (uint8_t i = 0; i < times; i++) {
        PORTB = 0xff;
        _delay_ms(delay_time * 100);
        PORTB = 0x00;
        _delay_ms(delay_time * 100);
    }
}

void display_string(char *string) {
    for (int i = 0; i < strlen(string); i++) {
        // display only the characters available in the font
        // and silently ignore the others
        if (0x20 <= string[i] && string[i] < 0x7F)
            display_character(string[i]);
    }
    // wait a little bit after the string is finished
    _delay_ms(8 * delay_time);
}

void display_character(char character) {
    for (int i = 0; i < character_length; i++) {
        // the font array begins with ascii character 0x20 (SPACE)
        // shift index accordingly: font[0] equals 0x20
        display_byte(font[character - 0x20][i]);
    }
    // wait a little bit after the character is finished
    _delay_ms(2 * delay_time);
}

void display_byte(char byte) {
    PORTB = byte;
    // wait a little bit after the byte is finished
    _delay_ms(delay_time);
    // clear the port
    PORTB = 0;
}