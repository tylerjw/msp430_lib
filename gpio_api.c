/* msp430_lib.c - msp430 Microcontroller library
 */

#include "gpio_api.h"

/* _validate_pin - validates (port,pin) value
 * @param port (1,2)
 * @param pin  (0-7)
 * @returns true if pin is valid, false if not
 */
bool _validate_pin(int port, int pin)
{
    if(port < 1 || port > 2)
        return false;
    else if(pin < 0 || pin > 7)
        return false;
    return true;
}

bool gpio_init (int port, int pin, int direction)
{
    int nbit = ~(1 << pin);     // inverted bit mask
    if(direction)
        direction = ~bit;       // direction mask

    if (!_validate_pin(port,pin))
        return false;

    if (port == 1)
    {
        P1SEL &= nbit;      // set as gpio
        P1SEL2 &= nbit;     // (0,0) = gpio pin
        P1OUT &= nbit;      // set output to zero
        P1DIR |= direction; // set direction
    }
    else                    // port 2
    {
        P2SEL &= nbit;      // set as gpio
        P2SEL2 &= nbit;     // (0,0) = gpio pin
        P2OUT &= nbit;      // set output to zero
        P2DIR |= direction; // set direction
    }
    return true;
}

bool gpio_ioctl_pull_en(int port, int pin, int direction)
{
    int mask = 1 << pin;    // mask for setting pin
    if(direction)
        direction = mask;

    if (!_validate_pin(port,pin))
        return false;

    if (port == 1)
    {
        P1OUT |= direction;  // pull up/down
        P1REN |= mask;
    }
    else            // port 2
    {
        P2OUT |= direction;  // pull up/down
        P2REN |= mask;
    }
    return true
}

bool gpio_write(int port, int pin, int value)
{
    if (value)              
        value = 1 << pin;   // mask for setting pin

    if (!_validate_pin(port,pin))
        return false;

    if (port == 1)
        P1OUT |= value; // set output
    else:               // port 2
        P2OUT |= value; // set output
    return true;
}

int  gpio_read (int port, int pin)
{
    int mask = 1 << pin;
    value = 0;

    if (!_validate_pin(port,pin))
        return -1;

    if(port == 1)
    {
        if (P1IN & mask)
            value = 1;
    }
    else        // port 2
    {
        if(P2IN & mask)
            value = 1;
    }
    return value;
}