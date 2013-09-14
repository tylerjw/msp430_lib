/* gpio_api.h - General Purpose Input/Output API
*/

#ifndef MSP_GPIO_API_H
#define MSP_GPIO_API_H

#include <msp430g2553.h>
#include <stdbool.h>
#include <stdint.h>

// null
#define NULL ((void *)0)

#define INPUT   0
#define OUTPUT  1
#define DOWN    0
#define UP      1

/* gpio object
 * stores mask for the bit associated with indevidual pin ( or pins )
 * and pointers to the memory location of registers.
*/
typedef struct {
	uint8_t mask;
	uint16_t *reg_out;
	uint16_t *reg_in;
	uint16_t *reg_ren;
	uint16_t *reg_dir;
} gpio_t;

/* gpio_init - initialize GPIO pin
 * @param obj gpio object pointer
 * @param port (1,2)
 * @param pin  (0-7)
 * @param direction (INPUT or OUTPUT) or (0,1)
 * @returns NULL if error, obj pointer otherwise
 */
gpio_t *gpio_init(gpio_t *obj, int port, int pin, int direction);

/* gpio_ioctl_pull_en - enable pull up (input)
 * @param obj gpio object pointer
 * @param direction (DOWN or UP) or (0,1)
 */
void gpio_ioctl_pull_en(gpio_t *obj, int direction);

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