/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <avr/interrupt.h> /* Obligatorio para usar la ISR y cli()/sei() */

#define BUFFER_SIZE 64

volatile uint8_t rx_buffer[BUFFER_SIZE];
volatile uint8_t rx_head = 0; /* Índice de escritura (lo usa la ISR) */
volatile uint8_t rx_tail = 0; /* Índice de lectura (lo usa el main) */

#include "serial.h"

#include <stdint.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/* bits importantes segun el manual */
#define RXEN0 4
#define TXEN0 3
#define UCSZ01 2
#define UCSZ00 1
#define UDRE0 5
#define RXC0 7

typedef struct {
  uint8_t status_control_a; /* 0xC0: UCSR0A */
  uint8_t status_control_b; /* 0xC1: UCSR0B */
  uint8_t status_control_c; /* 0xC2: UCSR0C */
  uint8_t reserved;         /* 0xC3: espacio reservado*/
  uint8_t baud_rate_low;    /* 0xC4: UBRR0L */
  uint8_t baud_rate_high;   /* 0xC5: UBRR0H */
  uint8_t data_es;          /* 0xC6: UDR0 */
} volatile uart_t;

/* puntero a la base de los registros USART0 */
uart_t* puerto_serial = (uart_t*)(0xc0);

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/* inicializa el driver SIN bit de paridad y SIN bit de stop */
void serial_init() {
  puerto_serial->baud_rate_high = (uint8_t)(BAUD_PRESCALE >> 8);
  puerto_serial->baud_rate_low = (uint8_t)(BAUD_PRESCALE);

  puerto_serial->status_control_c = (1 << UCSZ01) | (1 << UCSZ00);
  puerto_serial->status_control_b = (1 << RXEN0) | (1 << TXEN0);
}

/* envia un char */
void serial_put_char(char c) {
  while (!(puerto_serial->status_control_a & (1 << UDRE0))) {
  }

  puerto_serial->data_es = c;
}

/* recibe un char */
char serial_get_char(void) {
  while (!(puerto_serial->status_control_a & (1 << RXC0))) {
  }

  return puerto_serial->data_es;
}

/* envia un float de 4 bytes */
void serial_put_float(float c) {
  uint8_t* ptr = (uint8_t*)&f;

  for (int i = 0; i < 4; i++) {
    serial_put_char(ptr[i]);
  }
}

/* recibe un float de 4 bytes */
char serial_get_float(void) {
  float f;
  uint8_t* ptr = (uint8_t*)&f;

  for (int i = 0; i < 4; i++) {
    ptr[i] = serial_get_char();
  }

  return f;
}

/* envia un int de 2 bytes */
void serial_put_int(int16_t c) {
  uint8_t* ptr = (uint8_t*)&f;

  for (int i = 0; i < 2; i++) {
    serial_put_char(ptr[i]);
  }
}

/* recibe un int de 2 bytes */
char serial_get_int(void) {
  int16_t f;
  uint8_t* ptr = (uint8_t*)&f;

  for (int i = 0; i < 2; i++) {
    ptr[i] = serial_get_char();
  }

  return f;
}