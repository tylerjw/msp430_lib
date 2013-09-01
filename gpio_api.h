/* gpio_api.h - General Purpose Input/Output API
*/

#ifndef MSP_GPIO_API_H
#define MSP_GPIO_API_H

#include  <msp430g2553.h>

#define INPUT   0
#define OUTPUT  1
#define DOWN    0
#define UP      1

/* gpio_init - initialize GPIO pin
 * @param port (1,2)
 * @param pin  (0-7)
 * @param direction (INPUT or OUTPUT) or (0,1)
 * @returns true if configured, else false if error
 */
bool gpio_init(int port, int pin, int direction);

/* gpio_ioctl_pull_en - enable pull up (input)
 * @param port (1,2)
 * @param pin  (0-7)
 * @param direction (DOWN or UP) or (0,1)
 */
bool gpio_ioctl_pull_en(int port, int pin, int direction);

/* gpio_write - write to GPIO pin
 * @param port (1,2)
 * @param pin  (0-7)
 * @param value (0,1)
 * @returns true if set, else false if error
 */
bool gpio_write(int port, int pin, int value);

/* gpio_read - write to GPIO pin
 * @param port (1,2)
 * @param pin  (0-7)
 * @returns 1 if set
            0 if unset
            -1 if error
 */
int  gpio_read (int port, int pin);

#endif