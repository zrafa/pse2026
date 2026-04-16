
/* utils.c - funciones de soporte al programa principal */

/* puertos de E/S */

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDRB (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PINB (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;

/* ------------------------------------------------------- */

/* direccion de PORTC (registro de datos) */
volatile unsigned char * puerto_c = (unsigned char *) 0x28;

/* direccion de DDRC (registro de control) */
volatile unsigned char * ddr_c = (unsigned char *) 0x27;

/* direccion PINC (registro de datos de entrada) */
volatile unsigned char * pin_c = (unsigned char *) 0x26;

/* ------------------------------------------------------- */

volatile unsigned char imagenes[3][8] = {
	{ // cohete
		0b00011000,
		0b00111100,
		0b01100110,
		0b11111111,
		0b01111110,
		0b00100100,
		0b01011010,
		0b10000001
	},
	{ // corazon
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000,
		0b00000000
	},
	{ // mariposa
    	0b01000010,
    	0b11100111,
    	0b11111111,
    	0b01111110,
		0b00111100,
		0b01111110,
		0b11000011,
		0b10000001
	}
};

volatile unsigned char iteracion = 0;
volatile char direccion = 1; // 1 -> derecha, -1 -> izquierda
volatile unsigned char imagen_actual = 0;
volatile unsigned char cant_imagenes = sizeof(imagenes) / sizeof(imagenes[0]);

/* permite hacer un delay de n milisegundos */
void delayms(int n) {
	volatile unsigned int i, j;

	for(i = 0; i < n; i++) {
		for(j = 0; j < 794; j++) {
			/* no hace nada, espera que el tiempo pase... */
		}
	}
}

/* led_init: configura el puertos de entrada y salida */
void led_init() {
	// registro b, bits: 0, 1, 2, 3 - SALIDA
	*ddr_b |= 1 << 0 | 1 << 1 | 1 << 2 | 1 << 3;

	// registro c, bits: 2, 3, 4, 5 - SALIDA
	*ddr_c |= 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5;

	// registro b, bit 4 - ENTRADA
	*ddr_b &= ~(1 << 4);

	// activamos el pull-up
	*puerto_b |= 1 << 4;
}

void siguiente_animacion() {
	// cada led le corresponde siempre la misma posicion del arreglo de imagen
	// la iteracion indica a que bit se debe acceder

	// paso 1: borrar la animacion actual de los pines
	*puerto_b &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3);
	*puerto_c &= ~(1 << 2 | 1 << 3 | 1 << 4 | 1 << 5);

	// paso 2: revisar los leds que se tienen que prender en esta animacion
	unsigned char temp;

	// obtenemos el valor de los leds del puerto b
	for(int i = 0; i <= 3; i++) {
		// obtenemos la posicion correspondiente a un pin
		temp = imagenes[imagen_actual][i];
		// movemos a la derecha el bit que nos importa
		temp >>= iteracion;
		// borramos el resto de bits
		temp &= 1;

		// guardamos el nuevo valor en la salida
		*puerto_b |= temp << i;
	}

	// obtenemos el valor de los leds del puerto c
	for(int i = 2; i <= 5; i++) {
		// obtenemos la posicion correspondiente a un pin
		temp = imagenes[imagen_actual][i + 2];
		// movemos a la derecha el bit que nos importa
		temp >>= iteracion;
		// borramos el resto de bits
		temp &= 1;

		// guardamos el nuevo valor en la salida
		*puerto_c |= temp << i;
	}

	// paso 3: aumentar la iteracion hacia el lado indicado
	if(iteracion == 7) {
		// llego al fin de la derecha, cambia de lado
		iteracion = 6;
		direccion = -1;
	} else if(iteracion == 0) {
		// llego al fin de la izquierda, cambia de lado
		iteracion = 1;
		direccion = 1;
	} else {
		iteracion += direccion;
	}
}

void verificar_cambio_imagen() {
	// si se presiono el pulsados, se realiza cambio de imagen
	volatile unsigned char valor = *pin_b;

	// obtenemos el valor en la posicion 5 (0 desactivado - 1 activado)
	valor >>= 4;
	valor &= 1;


	if(!valor) {
		// se activo el pulsador, se debe realizar un cambio de imagen y reseteo de variables
		iteracion = 0;
		direccion = 1;
		imagen_actual = (imagen_actual + 1) % cant_imagenes;

		// se realiza una espera para evitar problemas por las oscilaciones que genera el pulsador
		delayms(100);
	}
}