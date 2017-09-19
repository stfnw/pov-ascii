#include <avr/io.h>     // for the pin definitions
#include "pov-ascii.h"

int main(void) {
    // -------- Initialize the ports --------- //
    DDRB = 0xff; /* Set up all of LED pins for output */

    flash(3);

    // ------ Event / main loop ------ //
    while (1) {
        char message[] = "Hello World!";

        display_string(message);
    }

    return 0;
}
