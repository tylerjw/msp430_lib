/* gpio_tests.c - for testing gpio library
 */

#include  <msp430g2553.h>
#include  "gpio_api.h"

void main(void)
{
    gpio_init(1,0,OUTPUT);      // red led
    gpio_init(1,6,OUTPUT);      // green led
    gpio_init(1,3,INPUT);       // button
    gpio_ioctl_pull_en(1,3,UP);  // pull up on button

    for(;;)
    {
        while(gpio_read(1,3) == 0);     // button is not pressed
        gpio_write(1,0,1);              // red on
        while(gpio_read(1,3) == 0);     // button is pressed
        goio_write(1,0,0);              // red off
        gpio_write(1,6,~gpio_read(1,6)) // toggle green
    }
}