
/* utils.c - funciones de soporte al programa principal */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328p
 * El puerto B de un atmega328p tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */


/* puertos de E/S */

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDR B (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PIN B (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;


void esperar() {
	volatile unsigned long i;
	/* delay de aprox. 1 segundo */
	for (i=0; i<50000; i++);
}

/* led_off: apaga el led conectado al puerto b bit 5 */
void pasarEstado(unsigned char estado) {
	*puerto_b = *puerto_b | estado;
	*puerto_b = *puerto_b & (estado | 0xE0);
}
/* led_init: configura el puerto b bit 5 como salida */
void led_init() {
	*ddr_b = 0x3F;
	*puerto_b = 0x20;
}
