#ifndef POVASCII_H
#define POVASCII_H

/* displays a string on the LEDs */
void display_string(char* string);

/* displays a character on the LEDs
 * the font is 8 pixels wide
 * the corresponding data is taken from the corresponding header file */
void display_character(char character);

/* displays a single byte on the 8 LEDs */
void display_byte(char byte);

#endif
