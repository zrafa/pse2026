#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <util/delay.h>

#define PIN_SOUND 0

#define TIEMPO 500000UL

/* puertos de E/S */
volatile unsigned char *puerto_b = (unsigned char *) 0x25; // PORTB (datos)
volatile unsigned char *ddr_b = (unsigned char *) 0x24; // DDRB (control)
volatile unsigned char *pin_b = (unsigned char *) 0x23; // PINB (entrada)

/* configura el puertos de salida */
void piano_init() {
	*ddr_b |= 1 << PIN_SOUND;
}

/* se transforma la nota traida como caracter a se valor correspondiente */
unsigned char transformar_nota(unsigned char nota) {
    volatile unsigned char nueva_nota = -1;

    switch(nota) {
    case 'a':
        nueva_nota = 0; break;
    case 's':
        nueva_nota = 1; break;
    case 'd':
        nueva_nota = 2; break;
    case 'f':
        nueva_nota = 3; break;
    case 'g':
        nueva_nota = 4; break;
    case 'h':
        nueva_nota = 5; break;
    case 'j':
        nueva_nota = 6; break;
    }

    return nueva_nota;
}

// guardamos el tiempo en microsegundos de un periodo para cada nota
unsigned int us_notas[] = {
    1911, // Do5
    1803, // Re5
    1517, // Mi5
    1431, // Fa5
    1276, // Sol5
    1136, // La5
    1012  // Si5
};

/* 0: do - 1: re - 2: mi - 3: fa - 4: sol - 5: la - 6: si */
void reproducir_nota(unsigned char nota) {
    unsigned int periodo = us_notas[nota];
    unsigned int medio_periodo = us_notas[nota] / 2;
    unsigned long tiempo = 0;
	
    // cada nota se ejecuta por medio segundo
    while(tiempo < TIEMPO) {
        // poner en alto la señal
		*puerto_b |= 1 << PIN_SOUND;
		// esperamos
		_delay_us(medio_periodo);
		// poner en bajo la señal
		*puerto_b &= ~(1 << PIN_SOUND);
		// esperamos
		_delay_us(medio_periodo);

        // aumentamos el tiempo
        tiempo += periodo;
    }
}