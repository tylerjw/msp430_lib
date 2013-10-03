/* tests method for assignment of pointers to hardware registers 
 * compile: msp430-gcc regptr_test.c -mmcu=msp430g2553 -Wall -g -o regptr_test.elf
 * load: mspdebug rf2500 [gdb]
 * debug: msp430-gdb --command=commands.gdb regptr_test.elf
*/

#include <msp430g2553.h>

#define INPUT   0
#define OUTPUT  1
#define DOWN    0
#define UP      1

#define NULL ((void *)0)    // NULL

 typedef struct {
	unsigned char mask;
	volatile unsigned char *reg_out;
	volatile unsigned char *reg_in;
	volatile unsigned char *reg_ren;
	volatile unsigned char *reg_dir;
} gpio_t;

/* gpio_init - initialize GPIO pin
 * @param obj gpio object pointer
 * @param port (1,2)
 * @param pin  (0-7)
 * @param io (INPUT or OUTPUT) or (0,1)
 * @returns NULL if error, obj pointer otherwise
 */
gpio_t *gpio_init(gpio_t *obj, int port, int pin, int io);

/* gpio_ioctl_pull_en - enable pull up (input)
 * @param obj gpio object pointer
 * @param updown (DOWN or UP) or (0,1)
 */
void gpio_ioctl_pull_en(gpio_t *obj, int updown);

/* gpio_write - write to GPIO pin (sets PxOUT register)
 * @param obj gpio object pointer
 * @param value (0,1)
 */
void gpio_write(gpio_t *obj, int value);

/* gpio_read - write to GPIO pin (reads PxIN register)
 * @param obj gpio object pointer
 * @returns 1 if set
            0 if unset
 */
int  gpio_read (gpio_t *obj);

int main(void)
{
	gpio_t led, button;

	gpio_init(&led, 1, 6, OUTPUT); // green led
	gpio_init(&button, 1, 3, INPUT);

	WDTCTL = WDTPW | WDTHOLD;   // disable wdt+
	
    gpio_ioctl_pull_en(&button, UP);
    gpio_write(&led, UP);

	for(;;) 
	{
        // (*button.reg_in & button.mask) != 0
		while(gpio_read(&button) == 1); // do nothing, button up
		gpio_write(&led, DOWN); // turn leds off
		while(gpio_read(&button) == 0); // do nothing, button is down
		gpio_write(&led, UP); // turn the leds on
	}
    return 0; // should never reach this!
}

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
