#include <avr/io.h>

void timer2_init_pwm(void) {
    // 1. Configurar los pines correspondientes al Timer2 como salida
    // OC2A corresponde a PB3 (Pin digital 11)
    // OC2B corresponde a PD3 (Pin digital 3)
    DDRB |= (1 << PB3);
    DDRD |= (1 << PD3);

    // 2. Configurar Timer2 en modo Fast PWM (Modo 3)
    // COM2A1=1, COM2A0=0 -> Salida no invertida en OC2A
    // COM2B1=1, COM2B0=0 -> Salida no invertida en OC2B
    // WGM21=1, WGM20=1 -> Fast PWM de 8 bits (Tope 0xFF)
    TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);

    // 3. Configurar Preescalador a 64 (CS22=1)
    // Con 16MHz, la frecuencia del PWM será: 16M / (64 * 256) = ~976 Hz
    // Es una frecuencia ideal y estándar para controlar motores DC pequeños y LEDs
    TCCR2B = (1 << CS22);

    // 4. Inicializar el ciclo de trabajo en 0 (Motor y LED apagados)
    OCR2A = 0;
    OCR2B = 0;
}

/* Función para actualizar la velocidad/brillo (0 a 255) */
void timer2_set_duty(uint8_t duty) {
    OCR2A = duty;  // Actualiza PWM en el pin 11
    OCR2B = duty;  // Actualiza PWM en el pin 3
}