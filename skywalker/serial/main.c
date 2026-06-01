#include "serial.h"

int main(void) {
    serial_init();
    serial_enable_rx_interrupt();

    while (1) {
        /* 1. El programa se bloquea esperando recibir EXACTAMENTE 2 bytes del buffer */
        int16_t numero_recibido = serial_get_int();

        /* 2. Operación matemática en el microcontrolador */
        numero_recibido = numero_recibido + 1;

        /* 3. Devuelve los 2 bytes modificados */
        serial_put_int(numero_recibido);
    }
    return 0;
}