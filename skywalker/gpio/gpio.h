/* gpio.h
 * 
 * API para la aplicacion embebida 
 * META: ocultar el hardware a la aplicacion 
 *
 */
#include <stdint.h>

#define NULL 0

#define LOW 0
#define HIGH 1

/* PBn */
#define D8  0
#define D9  1
#define D10 2
#define D11 3
#define D12 4
#define D13 5

/* PCn */
#define A0  8
#define A1  9
#define A2  10
#define A3  11
#define A4  12
#define A5  13

/* PDn */
#define TX1 16
#define RX0 17
#define D2  18
#define D3  19
#define D4  20
#define D5  21
#define D6  22
#define D7  23

/* Ports */
#define PORT_B  0
#define PORT_C  1
#define PORT_D  2

#ifndef _GPIO_H
#define _GPIO_H

int8_t gpio_input(uint8_t pin, int8_t pull_up);
int8_t gpio_output(uint8_t pin);
int8_t gpio_read(uint8_t pin);
int8_t gpio_write(uint8_t pin, uint8_t value);
int8_t gpio_toggle(uint8_t pin);
int8_t gpio_read_port(uint8_t port_name);
int8_t gpio_write_port(uint8_t port_name, uint8_t values);

#endif /* _GPIO_H */