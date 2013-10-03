/* gpio_tests.c - for testing gpio library
 */

#include "msp430_lib.h"

int main(void)
{
    gpio_t green, red, button;

    gpio_init(&green, 1, 6, OUTPUT); // green led
    gpio_init(&red, 1, 0, OUTPUT); // red led
    gpio_init(&button, 1, 3, INPUT);

    WDTCTL = WDTPW | WDTHOLD;   // disable wdt+
    
    gpio_ioctl_pull_en(&button, UP);
    gpio_write(&green, UP);
    gpio_write(&red, DOWN);

    for(;;) 
    {
        // (*button.reg_in & button.mask) != 0
        while(gpio_read(&button) == 1); // do nothing, button up
        gpio_write(&green, DOWN); // turn green off
        gpio_write(&red, UP); // turn red on
        while(gpio_read(&button) == 0); // do nothing, button is down
        gpio_write(&green, UP); // turn the green on
        gpio_write(&red, DOWN); // turn red off
    }
    return 0; // should never reach this!
}