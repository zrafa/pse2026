/*
 * ultrasound: controla el sensor HC-SR04 para medir distancias en cm
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU   16000000UL
#include <util/delay.h>
#include <avr/io.h>

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDR B (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PIN B (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;

/* Definimos los bits que vamos a usar */
#define TRIG_BIT 0  // PB0
#define ECHO_BIT 1  // PB1

/* ultrasound_get_distance()
 * 	devuelve la distancia en cm del objeto delante del sensor
 * 	devuelve -1 si no existe ningun objeto
 */
void ultrasound_init()
{
	*ddr_b |= (1 << TRIG_BIT);
	*ddr_b &= ~(1 << ECHO_BIT);
}

int ultrasound_get_distance(void)
{
	long duracion = 0;
	int distancia = -1;
	
	// Aseguro que el Trigger empiece en bajo
    *puerto_b &= ~(1 << TRIG_BIT);
    _delay_us(2); //Se usa para asegurar que el pin esté bien "limpio" en bajo antes de mandar el pulso. Es una medida de estabilidad.

    // Lanzar el pulso de Trigger (10 microsegundos) pdf de ultrasonic. Esta accion envia 8 ciclos de rafaga a 40Khz y levanta un Echo Pin
    *puerto_b |= (1 << TRIG_BIT);
    _delay_us(10); 
    *puerto_b &= ~(1 << TRIG_BIT);

	// Esperar a que el pin ECHO se ponga en ALTO (inicio del pulso)
    uint32_t timeout = 100000;
    while (!(*pin_b & (1 << ECHO_BIT)) && timeout > 0) {
        timeout--;
    }

    if (timeout == 0) return -1; // Error o sensor no conectado


	//  Contar cuánto tiempo el pin ECHO está en ALTO
    // Usamos un contador y un delay de 1 us para medir el ancho del pulso
    while (*pin_b & (1 << ECHO_BIT)) {
        duracion++;
        _delay_us(1);
        
        if (duracion > 30000) break; // Timeout si no hay objeto cerca
    }

    // Cálculo de distancia
    // El sonido tarda 58 microsegundos en ir y volver por cada cm.
    distancia = (int)(duracion / 58);

    // El sensor HC-SR04 tiene un rango de 2cm a 400cm
    if (distancia < 2 || distancia > 400) {
        return -1;
    }

	//_delay_us(1000);  /* espero 1000 microsegundos (1 milisegundo) */ //Porque?

	return distancia;
}
