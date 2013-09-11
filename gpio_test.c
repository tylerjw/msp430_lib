/* gpio_tests.c - for testing gpio library
 */

#include  "msp430_lib.h"

void main(void)
{
    int led = 0;
    gpio_t red_led;
    gpio_t green_led;
    gpio_t btn;
    gpio_init(&red_led,1,0,OUTPUT);      // red led
    gpio_init(&green_led,1,6,OUTPUT);      // green led
    gpio_init(&btn,1,3,INPUT);       // button
    gpio_ioctl_pull_en(&btn,UP);  // pull up on button

    for(;;)
    {
        while(gpio_read(&btn) == 1);     // button is not pressed
        while(gpio_read(&btn) == 0);     // button is pressed
        gpio_write(&red_led,1);              // red off
    }
}