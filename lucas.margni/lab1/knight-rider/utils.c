
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

unsigned char estado_animacion[] = {
	0b00000001,
	0b00000011,
	0b00000111,
	0b00001110,
	0b00011100,
	0b00011000,
	0b00010000
};

unsigned char cant_animaciones = sizeof(estado_animacion) / sizeof(estado_animacion[0]);

unsigned char estado_actual = 0; // animacion a mostrar
unsigned char direccion = 0; // 0: avanzar, 1: retroceder


/* led_init: configura el puerto b bit 0 a 4 como salida */
void led_init() {
	// Se debe poner el bit del 0 al 4 del registro PORTB en 1 para indicar que son de salida
	*ddr_b |= 0x1f;
}

void esperar() {
	volatile unsigned long i;
	/* delay */
	for (i=0; i<100000; i++);
}

void siguiente_animacion() {
	// se sigue la secuencia de estado_animacion
	*puerto_b = estado_animacion[estado_actual];

	if(direccion == 0) {
		// siguiente animacion
		if(estado_actual == cant_animaciones-1) {
			// terminamos las animaciones, retrocedemos
			estado_actual--;
			direccion = 1;
		} else {
			estado_actual++;
		}
	} else {
		// anterior animacion
		if(estado_actual == 0) {
			// llegamos al inicio, avanzamos nuevamente
			estado_actual++;
			direccion = 0;
		} else {
			estado_actual--;
		}
	}
}