#include <stdint.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer2.h"
#include "serial.h"

// Función auxiliar para imprimir números de 2 dígitos con cero inicial
void print_dos_digitos(uint16_t valor) {
    serial_put_char((valor / 10) + '0');
    serial_put_char((valor % 10) + '0');
}

int main(void) {
    serial_init();
    timer2_init();

    while (1) {
        // 1. Captura atómica de la variable global (para evitar errores de lectura)
        cli();
        uint32_t total_ticks = ticks_centis;
        sei();

        // 2. Desglosar tiempo
        uint8_t centesimas = total_ticks % 100;
        uint32_t total_segundos = total_ticks / 100;
        uint8_t segundos = total_segundos % 60;
        uint8_t minutos = (total_segundos / 60) % 60;

        // 3. Salida formateada: \r00:00:00
        serial_put_char('\r'); // Volver al inicio de la línea
        print_dos_digitos(minutos);
        serial_put_char(':');
        print_dos_digitos(segundos);
        serial_put_char(':');
        print_dos_digitos(centesimas);

        // Esperar un poco para no saturar el buffer serial
        _delay_ms(10);
    }
}