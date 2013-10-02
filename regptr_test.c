/* tests method for assignment of pointers to hardware registers */

#include <msp430g2553.h>

#define LEDS    (BIT0|BIT6)

void main(void)
{
	volatile unsigned char *reg;
	reg = (unsigned char *) &P1DIR; // P1DIR  0x0022

	WDTCTL = WDTPW | WDTHOLD;   // disable wdt+
	*reg |= LEDS;				// output enable leds

	reg = (unsigned char *) &P1OUT; // P1OUT  0x0021
	*reg |= LEDS;
 
	for(;;); // eternal loop
}