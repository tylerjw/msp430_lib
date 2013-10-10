/* gpio_api.h - General Purpose Input/Output API
*/

#ifndef MSP_GPIO_API_H
#define MSP_GPIO_API_H

#include  <msp430g2553.h>
#include "defines.h"

#define INPUT   0
#define OUTPUT  1
#define DOWN    0
#define UP      1
#define RISING	0
#define FALLING	1

/* gpio object
 * stores mask for the bit associated with indevidual pin ( or pins )
 * and pointers to the memory location of registers.
*/
typedef struct {
	unsigned char mask;
	volatile unsigned char *reg_out;
	volatile unsigned char *reg_in;
	volatile unsigned char *reg_ren;
	volatile unsigned char *reg_dir;
	volatile unsigned char *reg_ie;
	volatile unsigned char *reg_ies;
} gpio_t;

/* gpio_init - initialize GPIO pin
 * @param obj gpio object pointer
 * @param port (1,2)
 * @param pin  (0-7)
 * @param io (INPUT or OUTPUT) or (0,1)
 * @returns NULL if error, obj pointer otherwise
 */
gpio_t *gpio_init(gpio_t *obj, int port, int pin, int io);

/* gpio_ioctl_pull_en - enable pull (input)
 * @param obj gpio object pointer
 * @param updown (DOWN or UP) or (0,1)
 */
void gpio_ioctl_pull_en(gpio_t *obj, int updown);

/* gpio_ioctl_pull_dis - dissable pull
 * &param obj 	gpio object pointer
 */
void gpio_ioctl_pull_dis(gpio_t *obj);

/* gpio_ioctl_int_en - enable interrupt (input)
 * @param obj 	gpio object pointer
 * @param edge	edge to trigger interrupt (RISING or FALLING)
 */
void gpio_ioctl_int_en(gpio_t *obj, int edge);

/* gpio_ioctl_int_dis - disable interrupt (input)
 * @param obj 	gpio object pointer
 */
void gpio_ioctl_int_dis(gpio_t *obj);

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

#endif