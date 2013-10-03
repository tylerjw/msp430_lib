/* msp430_lib.c - msp430 Microcontroller library
 */

#include "gpio_api.h"

gpio_t *gpio_init (gpio_t *obj, int port, int pin, int io)
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

    obj->mask = (unsigned char)(1 << pin);     // bit mask
    if(io != 0)
    {
        io = (unsigned char)(1 << pin);      // io mask
    }

    if (port == 1)
    {
        obj->reg_dir = (unsigned char *) &P1DIR;
        obj->reg_out = (unsigned char *) &P1OUT;
        obj->reg_in = (unsigned char *) &P1IN;
        obj->reg_ren = (unsigned char *) &P1REN;

        P1SEL &= ~obj->mask;      // set as gpio
        P1SEL2 &= ~obj->mask;     // (0,0) = gpio pin
    }
    else                    // port 2
    {
        obj->reg_dir = (unsigned char *) &P2DIR;
        obj->reg_out = (unsigned char *) &P2OUT;
        obj->reg_in = (unsigned char *) &P2IN;
        obj->reg_ren = (unsigned char *) &P2REN;

        P2SEL &= ~obj->mask;      // set as gpio
        P2SEL2 &= ~obj->mask;     // (0,0) = gpio pin
    }

    *obj->reg_out &= ~obj->mask; // set output to 0 (pull down if input)
    *obj->reg_dir |= ((io == INPUT) ? INPUT : obj->mask); // set direction

    return obj;
}

void gpio_ioctl_pull_en(gpio_t* obj, int updown)
{
    *obj->reg_out |= ((updown == DOWN) ? DOWN : obj->mask); // set updown
    *obj->reg_ren |= obj->mask;
}

void gpio_write(gpio_t* obj, int value)
{
    if(value == UP)
    {
        *obj->reg_out |= obj->mask;
    } else {
        *obj->reg_out &= ~obj->mask;
    }
}

int  gpio_read (gpio_t* obj)
{
    return ((*obj->reg_in & obj->mask) ? UP : DOWN);
}
