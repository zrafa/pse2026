/*
 * ultrasound: controla el sensor HC-SR04 para medir distancias en cm
 */

#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU   16000000UL
#include <util/delay.h>
#include <avr/io.h>

/* dirección de PORT Trigger */
volatile unsigned char * port_trigger;

/* direccion de DDR Trigger */
volatile unsigned char * ddr_trigger;

/* n° de bit de trigger */
volatile unsigned char trigger_bit_number;

/* direccion de DDR Trigger */
volatile unsigned char * ddr_echo;

/* direccion PIN Trigger */
volatile unsigned char * pin_echo;

/* n° de bit de echo */
volatile unsigned char echo_bit_number;

/* CONSTANTES DE DIRECCIONES */
#define PUERTO_D 0x2B  
#define DDR_D 0x2A
#define PIN_D 0x29
#define PUERTO_C 0x28  
#define DDR_C 0x27
#define PIN_C 0x26
#define PUERTO_B 0x25  
#define DDR_B 0x24
#define PIN_B 0x23

void ultrasound_init(char trigger_num, char echo_num)
{
	//	Determina los puertos, ddr y pin de trigger y echo
	
	if(trigger_num >= 0 && trigger_num <= 5){
		// Del 0 al 8 se considera puerto B, el bit 6 y 7 no se usa
		port_trigger = (unsigned char *) PUERTO_B;
		ddr_trigger = (unsigned char *) DDR_B;
		trigger_bit_number = trigger_num;
	} else if (trigger_num >= 8 && trigger_num <= 13){
		// Del 0 al 8 se considera puerto C, el bit 6 y 7 no se usa
		port_trigger = (unsigned char *) PUERTO_C;
		ddr_trigger = (unsigned char *) DDR_C;
		trigger_bit_number = trigger_num - 8;
	} else if (trigger_num >= 16 && trigger_num <= 23){
		// Del 0 al 8 se considera puerto D
		port_trigger = (unsigned char *) PUERTO_D;
		ddr_trigger = (unsigned char *) DDR_D;
		trigger_bit_number = trigger_num - 16;
	} else {
		return;
	}
	
	if(echo_num >= 0 && echo_num <= 5){
		// Del 0 al 8 se considera puerto B, el bit 6 y 7 no se usa
		ddr_echo = (unsigned char *) DDR_B;
		pin_echo = (unsigned char *) PIN_B;
		echo_bit_number = echo_num;
	} else if (echo_num >= 8 && echo_num <= 13){
		// Del 0 al 8 se considera puerto C, el bit 6 y 7 no se usa
		ddr_echo = (unsigned char *) DDR_C;
		pin_echo = (unsigned char *) PIN_C;
		echo_bit_number = echo_num - 8;
	} else if (echo_num >= 16 && echo_num <= 23){
		// Del 0 al 8 se considera puerto D
		ddr_echo = (unsigned char *) DDR_D;
		pin_echo = (unsigned char *) PIN_D;
		echo_bit_number = echo_num - 16;
	} else {
		return;
	}
	
	*ddr_trigger |= (1 << trigger_bit_number);
	*ddr_echo &= ~(1 << echo_bit_number);
}

int ultrasound_get(void)
{
	long duration = 0;
	int distance = -1;
	
	// Asegura que el Trigger empiece en bajo
	*port_trigger &= ~(1 << trigger_bit_number);
	_delay_us(2); //Se usa para asegurar que el pin esté bien "limpio" en bajo antes de mandar el pulso. Es una medida de estabilidad.

	// Lanzar el pulso de Trigger (10 microsegundos) pdf de ultrasonic. 
	//Esta accion envia 8 ciclos de rafaga a 40Khz y levanta un Echo Pin
	*port_trigger |= (1 << trigger_bit_number);
	_delay_us(10); 
	*port_trigger &= ~(1 << trigger_bit_number);

	// Esperar a que el pin ECHO se ponga en ALTO (inicio del pulso)
	uint32_t timeout = 100000;
	while (!(*pin_echo & (1 << echo_bit_number)) && timeout > 0) {
		timeout--;
	}

	if (timeout == 0) return -1; // Error o sensor no conectado


	//  Contar cuánto tiempo el pin ECHO está en ALTO
	// Usamos un contador y un delay de 1 us para medir el ancho del pulso
	while (*pin_echo & (1 << echo_bit_number)) {
		duration++;
		_delay_us(1);
        
		if (duration > 30000) break; // Timeout si no hay objeto cerca
	}

	// Cálculo de distance
	// El sonido tarda 58 microsegundos en ir y volver por cada cm.
	distance = (int)(duration / 58);

	// El sensor HC-SR04 tiene un rango de 2cm a 400cm
	if (distance < 2 || distance > 400) {
		return -1;
	}

	return distance;
}
