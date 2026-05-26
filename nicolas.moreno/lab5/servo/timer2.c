#include <avr/io.h>

void timer1_init_servo(void) {
    // Configurar PB1 (Pin Digital 9) como salida para generar la señal PWM (OC1A)
    DDRB |= (1 << PB1);

    // onfigurar Timer1 en Modo 14 
    TCCR1A = (1 << COM1A1) | (1 << WGM11);

    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);

    // 50 Hz exactos
    ICR1 = 4999;

    OCR1A = 375;
}

/* Función para mover el servo. Recibe un valor entre 250 (1ms) y 500 (2ms) */
void timer1_set_servo(uint16_t duty) {
    if (duty < 250) duty = 250; 
    if (duty > 500) duty = 500; 
    
    OCR1A = duty;
}