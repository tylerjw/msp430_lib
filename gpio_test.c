/* gpio_tests.c - for testing gpio library
 */

#include  "msp430_lib.h"

void main(void)
{
    int led = 0;
    gpio_init(1,0,OUTPUT);      // red led
    gpio_init(1,6,OUTPUT);      // green led
    gpio_init(1,3,INPUT);       // button
    gpio_ioctl_pull_en(1,3,UP);  // pull up on button

    for(;;)
    {
        while(gpio_read(1,3) == 1);     // button is not pressed
        while(gpio_read(1,3) == 0);     // button is pressed
        gpio_write(1,0,1);              // red off
    }
}