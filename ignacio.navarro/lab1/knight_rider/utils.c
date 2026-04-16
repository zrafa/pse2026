volatile unsigned char * puerto_b = (unsigned char *) 0x25;
volatile unsigned char * ddr_b = (unsigned char *) 0x24;
volatile unsigned char * pin_b = (unsigned char *) 0x23;

void esperar() {
	volatile unsigned long i;
	/* delay de aprox. 1 segundo */
	for (i=0; i<50000; i++);
}

// configura 5 bits como salida
void led_init() {
	*(puerto_b) = 0;
	*(ddr_b) = 0b00011111;
}

// cambia segun el estado
void cambiar(char estado) {
	*(puerto_b) = estado;
}
