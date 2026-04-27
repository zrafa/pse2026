
/* utils.c - funciones de soporte al programa principal */

// Va pasando por estados, misma estructura que knight rider, pero con
//	otros estados, para formar una cara a gran velocidad
//	Se utilizan los puertos b, c y d

/* puertos de E/S */

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDR B (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PIN B (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;


/* puertos de E/S */

/* direccion de PORTC (registro de datos) */
volatile unsigned char * puerto_c = (unsigned char *) 0x28;

/* direccion de DDR C (registro de control) */
volatile unsigned char * ddr_c = (unsigned char *) 0x27;

/* direccion PIN C (registro de datos de entrada) */
volatile unsigned char * pin_c = (unsigned char *) 0x26;


/* direccion de PORTD (registro de datos) */
volatile unsigned char * puerto_d = (unsigned char *) 0x2B;

/* direccion de DDR D (registro de control) */
volatile unsigned char * ddr_d = (unsigned char *) 0x2A;

/* direccion PIN D (registro de datos de entrada) */
volatile unsigned char * pin_d = (unsigned char *) 0x29;

volatile unsigned char aux_b;

volatile unsigned char aux_c;

volatile unsigned char aux_d;


/* led_init: configura el puerto b y d como salida */
void led_init() {
	aux_b = 0x3F;
	aux_c = 0x30;
	aux_d = 0xFF;
	*ddr_b = aux_b;
	*ddr_c = aux_c;
	*ddr_d = aux_d;
}

void esperar(int cantidad_ms) {
	volatile unsigned long i;
	/* delay ajustable de ms */
	for (i=0; i<452 * cantidad_ms; i++);
}


/* led_off: apaga el led conectado al puerto b bit 5 */
void pasarEstado(unsigned char estado_b, unsigned char estado_d) {
	*puerto_b = *puerto_b | (estado_b & aux_b);
	*puerto_b = *puerto_b & (estado_b | ~aux_b);
	//  Hace shift 2 a la derecha el estado b, esto es para utilizar
	//	los bits 6 y 7 de estado para modificar los 4 y 5 de c
	*puerto_c = *puerto_c | ((estado_b >> 2) & aux_c);
	*puerto_c = *puerto_c & ((estado_b >> 2)| ~aux_c);
	*puerto_d = estado_d;
}

