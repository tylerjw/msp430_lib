 /**
 gpio_isr.c - demo of gpio isr on port 1.3 to catch button presses.
 **/

#include "msp430_lib.h"

volatile int button_counter = 0;

int main(void)
{
	gpio_t green, button;
	int led_state = 0;

    WDTCTL = WDTPW | WDTHOLD;   // disable wdt+

    gpio_init(&green, 1, 6, OUTPUT); // green led

    // confingure button
    gpio_init(&button, 1, 3, INPUT);
    // P1SEL &= ~(BIT3);
    // P1SEL2 &= ~(BIT3);
    // P1DIR &= ~(BIT3);
    gpio_ioctl_pull_en(&button, UP);
    //P1REN |= BIT3;
    //isr configure
    gpio_ioctl_int_en(&button, FALLING);
    // P1IES |= BIT3; // high to low interrupt
    // P1IE |= BIT3; // interrupt enabled

    _BIS_SR(GIE); // enable interrupts

    for(;;)
    {
    	if(button_counter > 0)
    	{
    		// toggle the led
			if(led_state == 1)
			{
				gpio_write(&green, 0);
				led_state = 0;
			} else {
				gpio_write(&green, 1);
				led_state = 1;
			}
			button_counter--;
    	}
    }
    return 0; // should never reach this!
}

/*
Port 1 ISR, gcc syntax

see: http://stackoverflow.com/questions/15500826/how-to-declare-an-interrupt-handler-isr-in-mspgcc
*/
static void
__attribute__((__interrupt__(PORT1_VECTOR)))
isr_gpio_p1 (void)
{
	if((P1IFG & BIT3) != 0) // button 3 generated the interrupt
	{
		button_counter++;
	}

	P1IFG &= 0x00; // clear the flagg
}