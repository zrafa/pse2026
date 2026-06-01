/**********************************************************************
 *
 * main.c - Aplicación de ejemplo (Capa de Usuario)
 *
 * NOTA: Este archivo es agnóstico del hardware gracias a serial.h
 *
 **********************************************************************/

#include "serial.h"

int main(void) {
  /* 1. Inicialización transparente del periférico */
  serial_init();

  /* 2. Activamos la magia de las interrupciones y el buffer asíncrono */
  serial_enable_rx_interrupt();

  /* 3. Saludo inicial al usuario a través de la terminal (CuteCom) */
  serial_put_str("==============================================\r\n");
  serial_put_str("  DRIVER UART ATMEGA328P INICIALIZADO (HAL)   \r\n");
  serial_put_str("==============================================\r\n");
  serial_put_str("Escribe caracteres en CuteCom para probar el eco...\r\n\n");

  while (1) {
    /* La aplicación solicita un byte al buffer de manera segura.
     Si no ha llegado nada por la antena RX, el flujo espera aquí
     sin desperdiciar ciclos del procesador en el registro de hardware.
     */
    char dato = serial_get_char_buffered();

    /*Procesamiento abstracto de la aplicación*/
    if (dato == '\r' || dato == '\n') {
      serial_put_str("\r\n[App]: Detectado un salto de linea.\r\n");
    } else {
      /*Generamos un eco visual de lo que procesó el buffer circular*/
      serial_put_str("Buffer Echo: [");
      serial_put_char(dato);
      serial_put_str("]\r\n");
    }
  }

  return 0; 
}