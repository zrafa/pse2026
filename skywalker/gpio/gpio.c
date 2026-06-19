/* gpio.c - Driver de pines GPIO del atmega328p
 *
 * META: ocultar el hardware a la aplicacion
 *
 * USO: primero se debe configurar los pines de input/output
 *	luego, se puede usar las funciones correspondientes segun se necesite
 */

#include "gpio.h"
#include <stdint.h>

typedef struct {
	uint8_t pin;    /* Input pin address (valores que recibe de entrada) */
	uint8_t ddr;    /* Data direction register (define el puerto como entrada o salida) */
	uint8_t port;   /* Data register (valores que se envían como salida) */
} volatile gpio_t;

volatile gpio_t *port_b = (gpio_t *)(0x23);
volatile gpio_t *port_c = (gpio_t *)(0x26);
volatile gpio_t *port_d = (gpio_t *)(0x29);

/* Funcion privada que mapea el pin con la estructura correspondiente
 * Devuelve NULL si input es invalido
 */
static gpio_t *gpio_port_map(uint8_t pin)
{
	if (pin >= 0 && pin <= 5)
		return port_b;
	else if (pin >= 8 && pin <= 13)
		return port_c;
	else if (pin >= 16 && pin <= 23)
		return port_d;
	else
		return NULL;
}

/* Funcion privada que mapea el nombre del puerto con la estructura correspondiente
 * Devuelve NULL si input es invalido
 */
static gpio_t *gpio_get_port(uint8_t port)
{
	if (port == PORT_B)
		return port_b;
	else if (port == PORT_C)
		return port_c;
	else if (port == PORT_D)
		return port_d;
	else
		return NULL;
}

/* Funcion privada que detecta los pins validos del port
 * Devuelve un byte con 1 en los pines validos, y en el resto 0
 * Se asume que el port pasado es valido
 */
static uint8_t gpio_valid_pins(uint8_t port)
{
	if (port == PORT_D)
		return 0xff;
	else
		return 0x3f;
}

/* Configura el pin como entrada
 * Devuelve -1 si pin es invalido, y 0 en otro caso
 */
int8_t gpio_input(uint8_t pin, int8_t pull_up)
{
	gpio_t *port = gpio_port_map(pin);
	uint8_t pin_port = pin % 8;

	if (port == NULL)
		return -1;

	port->ddr &= ~(1 << pin_port);

	if (pull_up)
		port->port |= (1 << pin_port);

	return 0;
}

/* Configura el pin como salida
 * Devuelve -1 si pin es invalido, y 0 en otro caso
 */
int8_t gpio_output(uint8_t pin)
{
	gpio_t *port = gpio_port_map(pin);
	uint8_t pin_port = pin % 8;

	if (port == NULL)
		return -1;

	port->ddr |= (1 << pin_port);

	return 0;
}

/* Lee un bit en el pin pasado
 * Devuelve -1 si pin es invalido o si no es de entrada, y el bit leido en otro caso
 */
int8_t gpio_read(uint8_t pin)
{
	gpio_t *port = gpio_port_map(pin);
	uint8_t pin_port = pin % 8;

	if (port == NULL)
		return -1;

	return ((port->pin >> (pin_port)) & 0x01);
}

/* Escribe value pin pasado (LOW/HIGH 0/1)
 * Devuelve -1 si pin es invalido, y 0 en otro caso
 */
int8_t gpio_write(uint8_t pin, uint8_t value)
{
	gpio_t *port = gpio_port_map(pin);
	uint8_t pin_port = pin % 8;

	if (port == NULL || value >= 2)
		return -1;

	/* borrar el bit que esta actualmente en la salida */
	port->port &= ~(1 << pin_port);

	/* escribimos value en la posición correspondiente */
	port->port |= (value << pin_port);

	return 0;
}

/* Modifica el bit en el pin pasado, escribiendo el opuesto
 * Devuelve -1 si pin es invalido, y 0 en otro caso
 */
int8_t gpio_toggle(uint8_t pin)
{
	gpio_t *port = gpio_port_map(pin);
	uint8_t pin_port = pin % 8;

	if (port == NULL)
		return -1;

	port->port ^= (1 << pin_port);

	return 0;
}

/* Lee todos los bits validos en el puerto pasado, en los invalidos deja 0
 * Devuelve -1 si el puerto es invalido, y los 8 bits leidos en otro caso
 */
int8_t gpio_read_port(uint8_t port_name)
{
	gpio_t *port = gpio_get_port(port_name);
	uint8_t valid_pins = gpio_valid_pins(port_name);

	if (port == NULL)
		return -1;

	return (port->pin & valid_pins);
}

/* Escribe los bits del port pasado con values
 * Se ignoran los valores de los pines invalidos
 * Devuelve -1 si port es invalido, y 0 en otro caso
 */
int8_t gpio_write_port(uint8_t port_name, uint8_t values)
{
	gpio_t *port = gpio_get_port(port_name);
	uint8_t valid_pins = gpio_valid_pins(port_name);

	if (port == NULL)
		return -1;

	/* borrar los bits que estan actualmente en el puerto */
	port->port &= ~(valid_pins);

	/* escribimos values en los pines validos */
	port->port |= (values & valid_pins);

	return 0;
}
