/* msp430_lib.c - msp430 Microcontroller library
 */

#include "gpio_api.h"

gpio_t *gpio_init (gpio_t *obj, int port, int pin, int direction)
{
    if(obj == NULL) 
    {
        return NULL;
    }
    // validate port/pin
    if(port < 1 || port > 2) 
    {
        return NULL;
    }
    else if(pin < 0 || pin > 7)
    {
        return NULL;
    }

    obj->mask = (1 << pin);     // bit mask
    if(direction != 0)
    {
        direction = (unsigned char)(1 << pin);      // direction mask
    }

    if (port == 1)
    {
        obj->reg_dir = &P1DIR;
        obj->reg_out = &P1OUT;
        obj->reg_in = &P1IN;
        obj->reg_ren = &P1REN;

        P1SEL &= ~obj->mask;      // set as gpio
        P1SEL2 &= ~obj->mask;     // (0,0) = gpio pin
    }
    else                    // port 2
    {
        obj->reg_dir = &P2DIR;
        obj->reg_out = &P2OUT;
        obj->reg_in = &P2IN;
        obj->reg_ren = &P2REN;

        P2SEL &= ~obj->mask;      // set as gpio
        P2SEL2 &= ~obj->mask;     // (0,0) = gpio pin
    }

    *obj->reg_out &= ~obj->mask; // set output to 0 (pull down if input)
    *obj->reg_dir |= ((direction != 0) ? obj->mask : 0); // set direction

    return obj;
}

void gpio_ioctl_pull_en(gpio_t* obj, int direction)
{
    *obj->reg_dir |= ((direction != 0) ? obj->mask : 0); // set direction
    *obj->reg_ren |= obj->mask;
}

void gpio_write(gpio_t* obj, int value)
{
    *obj->reg_out |= ((value != 0) ? obj->mask : 0);
}

int  gpio_read (gpio_t* obj)
{
    return ((*obj->reg_in & obj->mask) ? 1 : 0);
}