#include <stdint.h>
#include <avr/io.h>

// Estructura para el Timer 1 de 16 bits (¡Vuelve el 0x80!)
typedef struct {
    uint8_t controlA; // TCCR1A 0x80
    uint8_t controlB; // TCCR1B 0x81
    uint8_t controlC; // TCCR1C 0x82
    uint8_t reserved; // Salto  0x83
  
    uint16_t counter; // TCNT1  0x84
    uint16_t icr;     // ICR1   0x86 (Input Capture / Tope)
    uint16_t compareA;// OCR1A  0x88 (Ancho de pulso)
    uint16_t compareB;// OCR1B  0x8A
} volatile timer16;

volatile timer16 *timer1 = (volatile timer16 *)(0x80);

void servo_set_ticks(uint16_t ticks) {
    if(ticks < 2000) ticks = 2000;
    if(ticks > 4000) ticks = 4000;
    
    timer1->compareA = ticks;
}

void servo_init(void) {
    // 1. Configurar el Pin 9 (PB1) como salida física
    // DDRB es el registro de dirección de datos del Puerto B
    DDRB |= 0b00000010; 

    // 2. Configurar Fast PWM Modo 14 (TOP = ICR1) y Prescaler de 8
    // En Modo 14, los bits WGM13=1, WGM12=1, WGM11=1, WGM10=0
    // COM1A1=1, COM1A0=0 (Clear on compare match, set at BOTTOM)
    timer1->controlA = 0b10000010; 
    
    // CS11=1 (Prescaler 8) + WGM13 y WGM12 en 1
    timer1->controlB = 0b00011010; 

    // 3. Establecer el periodo total de la señal a 20ms (50Hz)
    timer1->icr = 39999; 

    // 4. Posición inicial segura: Centro (1.5ms = 3000 ticks)
    timer1->compareA = 3000; 
    
    // NOTA: ¡Aquí NO necesitamos interrupciones (TIMSK o SREG)! 
    // El hardware genera la señal eléctrica por su cuenta en segundo plano.
}
