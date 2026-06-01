/**********************************************************************
 *
 * serial.c - Driver del UART del atmega328p
 *
 * META : ocultar el hardware a la aplicacion
 *
 * Configuracion: 9600bps, 8bits data, 1bit stop, sin bit de paridad
 *
 **********************************************************************/

#include <avr/interrupt.h> 
#include <stdint.h>
#include "serial.h"

#define BUFFER_SIZE 64

volatile uint8_t rx_buffer[BUFFER_SIZE];
volatile uint8_t rx_head = 0; // Índice de escritura (lo usa la ISR)
volatile uint8_t rx_tail = 0; // Índice de lectura (lo usa el main)

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/* Bits importantes según el manual */
#define RXCIE0 7
#define RXEN0  4
#define TXEN0  3
#define UCSZ01 2
#define UCSZ00 1
#define UDRE0  5
#define RXC0   7

typedef struct {
  uint8_t status_control_a; /* 0xC0: UCSR0A */
  uint8_t status_control_b; /* 0xC1: UCSR0B */
  uint8_t status_control_c; /* 0xC2: UCSR0C */
  uint8_t reserved;         /* 0xC3: espacio reservado*/
  uint8_t baud_rate_low;    /* 0xC4: UBRR0L */
  uint8_t baud_rate_high;   /* 0xC5: UBRR0H */
  uint8_t data_es;          /* 0xC6: UDR0 */
} volatile uart_t;

uart_t* puerto_serial = (uart_t*)(0xc0);

#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

/* Inicializa el hardware en modo por encuesta (Polling) */
void serial_init() {
  puerto_serial->baud_rate_high = (uint8_t)(BAUD_PRESCALE >> 8);
  puerto_serial->baud_rate_low = (uint8_t)(BAUD_PRESCALE);

  puerto_serial->status_control_c = (1 << UCSZ01) | (1 << UCSZ00); /* 8 bits, 1 stop, no parity */
  puerto_serial->status_control_b = (1 << RXEN0) | (1 << TXEN0);   /* Habilita TX y RX */
}

/* Habilita las interrupciones de recepción */
void serial_enable_rx_interrupt(void) {
  puerto_serial->status_control_b |= (1 << RXCIE0);
  sei(); /* Habilita las interrupciones globales */
}

/* Se ejecuta cada vez que llega un byte */
ISR(USART_RX_vect) {
  uint8_t data = puerto_serial->data_es;
  uint8_t next_head = (rx_head + 1) % BUFFER_SIZE;

  /* Si el buffer NO está lleno, guardamos el byte. Si está lleno, se descarta. */
  if (next_head != rx_tail) {
    rx_buffer[rx_head] = data;
    rx_head = next_head;
  }
}

/* Envía un char (Polling) */
void serial_put_char(char c) {
  while (!(puerto_serial->status_control_a & (1 << UDRE0)));
  puerto_serial->data_es = c;
}

/* Envía una cadena de caracteres */
void serial_put_str(const char* str) {
  while (*str) {
    serial_put_char(*str++);
  }
}

/* Recibe un char por encuesta (sin usar el buffer) */
char serial_get_char(void) {
  while (!(puerto_serial->status_control_a & (1 << RXC0)));
  return puerto_serial->data_es;
}

/* Obtiene un valor desde el buffer circular usando interrupciones */
char serial_get_char_buffered(void) {
  /* Bloqueante si el buffer está vacío */
  while (rx_head == rx_tail); 

  cli();
  char c = rx_buffer[rx_tail];
  rx_tail = (rx_tail + 1) % BUFFER_SIZE;
  sei();

  return c;
}

/* Envía un float de 4 bytes  */
void serial_put_float(float f) {
  uint8_t* ptr = (uint8_t*)&f;
  for (int i = 0; i < 4; i++) {
    serial_put_char(ptr[i]);
  }
}

/* Recibe un float de 4 bytes usando el buffer circular */
float serial_get_float(void) {
  float f;
  uint8_t* ptr = (uint8_t*)&f;
  for (int i = 0; i < 4; i++) {
    ptr[i] = serial_get_char_buffered();
  }
  return f;
}

/* Envía un int de 2 bytes */
void serial_put_int(int16_t s) {
  uint8_t* ptr = (uint8_t*)&s;
  for (int i = 0; i < 2; i++) {
    serial_put_char(ptr[i]);
  }
}

/* Recibe un int de 2 bytes usando el buffer circular */
int16_t serial_get_int(void) {
  int16_t s;
  uint8_t* ptr = (uint8_t*)&s;
  for (int i = 0; i < 2; i++) {
    ptr[i] = serial_get_char_buffered();
  }
  return s;
}