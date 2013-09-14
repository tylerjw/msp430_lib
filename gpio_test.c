/* gpio_tests.c - for testing gpio library
 */

#include  "msp430_lib.h"

void main(void)
{
    int led = 0;
    gpio_t pins[3];
    gpio_t *red_led = &pins[0];
    gpio_t *green_led = &pins[1];
    gpio_t *btn = &pins[2];

    gpio_init(red_led,1,0,OUTPUT);      // red led
    gpio_init(green_led,1,6,OUTPUT);      // green led
    gpio_init(btn,1,3,INPUT);       // button

    gpio_ioctl_pull_en(btn,UP);  // pull up on button

    for(;;)
    {
        int i = 0;
        while(gpio_read(btn) == 1) i++;     // button is not pressed
        while(gpio_read(btn) == 0) i--;     // button is pressed
        gpio_write(red_led,1);              // red off
    }
}