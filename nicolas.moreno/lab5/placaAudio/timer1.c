#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/* Estructura Overlay para Timer1 (Dirección base 0x80) */
typedef struct {
    uint8_t tccr1a;  /* 0x80: Control Register A */
    uint8_t tccr1b;  /* 0x81: Control Register B */
    uint8_t tccr1c;  /* 0x82: Control Register C */
    uint8_t reserved;/* 0x83: Espacio vacío */
    uint16_t tcnt1;  /* 0x84 y 0x85: Counter Register (Acceso 16 bits) */
    uint16_t icr1;   /* 0x86 y 0x87: Input Capture Register (Tope Modo 14) */
    uint16_t ocr1a;  /* 0x88 y 0x89: Output Compare Register A (Audio D9) */
    uint16_t ocr1b;  /* 0x8A y 0x8B: Output Compare Register B */
} volatile timer1_t;

/* Puntero al bloque del Timer1 */
timer1_t *tmr1 = (timer1_t *) 0x80;

/* Registro de máscara de interrupción del Timer1 en 0x6F */
volatile uint8_t *timsk1 = (uint8_t *) 0x6F;

// Variable global que compartirá el Main con la ISR
volatile uint16_t muestra_actual = 0;

void timer1_init() {
    // 1. Configurar Pin D9 (PB1) como salida (OC1A)
    DDRB |= (1 << PB1);

    // 2. TCCR1A: COM1A1=1 (Clear on match), WGM11=1 (Parte de Modo 14)
    tmr1->tccr1a = (1 << COM1A1) | (1 << WGM11);

    // 3. TCCR1B: WGM13=1, WGM12=1 (Modo 14: Fast PWM con TOP en ICR1)
    tmr1->tccr1b = (1 << WGM13) | (1 << WGM12);

    // 4. Fijar TOP para la frecuencia de muestreo de 11025Hz (16MHz / 11025 = 1451)
    tmr1->icr1 = 1451;

    // 5. Habilitar interrupción por "Output Compare A" (OCIE1A)
    *timsk1 |= (1 << OCIE1A);

    // 6. Arrancar sin prescaler (CS10=1)
    tmr1->tccr1b |= (1 << CS10);

    // Inicializar el ancho de pulso en 0
    tmr1->ocr1a = 0;

    // Activar interrupciones globales si no estaban activas
    sei();
}

/* ISR: Se ejecuta exactamente 11025 veces por segundo */
ISR(TIMER1_COMPA_vect) {
    // Cargamos la muestra que el main dejó preparada y escalada
    tmr1->ocr1a = muestra_actual;
}