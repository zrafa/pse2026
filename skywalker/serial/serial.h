/**********************************************************************
 *
 * Filename:    serial.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

/**
 * Inicializa el módulo USART a 9600 bps, 8 bits de datos, 
 * 1 bit de parada y sin paridad (Modo por encuesta de forma nativa).
 */
void serial_init(uint8_t interruption_on);
/**
 * Activa las interrupciones de hardware para la recepción (RX)
 * y habilita el almacenamiento automático en el buffer circular.
 */
void serial_enable_rx_interrupt(void);

/**
 * Envía un único carácter de forma bloqueante por encuesta.
 */
void serial_put_char(char c);

/**
 * Transmite una cadena de caracteres terminada en null.
 */
void serial_put_str(const char *str);

/**
 * Lee un carácter directamente del hardware por encuesta (polling).
 */
char serial_get_char(void);

/**
 * Extrae un carácter desde el buffer circular de forma segura.
 * Si el buffer está vacío, la función se bloquea hasta que la ISR inserte un byte.
 */
char serial_get_char_buffered(void);

/**
 * Envía un número de punto flotante de 4 bytes en formato crudo (binario).
 */
void serial_put_float(float f);

/**
 * Lee un número de punto flotante de 4 bytes procesado a través del buffer circular.
 */
float serial_get_float(void);

/**
 * Envía un entero con signo de 16 bits (2 bytes) en formato crudo (binario).
 */
void serial_put_int(int16_t s);

/**
 * Lee un entero con signo de 16 bits procesado a través del buffer circular.
 */
int16_t serial_get_int(void);

#endif /* SERIAL_H */