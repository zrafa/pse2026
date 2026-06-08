#include <avr/interrupt.h>

#include "timer0.h"
#include "adc.h"

#include <math.h>

void main()
{
	/* ATENCION: SE ESTA USANDO EL ADC DE LOS TPS ANTERIORES, NO EL CREADO POR ESTOS DRIVERS
	PRIMERO PROBAR QUE FUNCIONA EL DRIVER DEL TIMER0, Y SI ESE ES EL CASO MODIFICAR ESTE ARCHIVO
	MAIN PARA USAR EL DRIVER DEL ADC CREADO POR NUESTROS COMPAÑEROS COMO CORRESPONDE
	COPIANDO EN LA CARPETA ACTUAL LOS ARCHIVOS ADC.C Y ADC.H NECESARIOS Y ELIMINAR ESTE COMENTARIO
	ESTO SE HACE PARA NO PROBAR EL FUNCIONAMIENTO DE TODO A LA VEZ. SALUDOS */
	timer0_init(MODE_PWM, PRESCALER_64, 255);
	adc_init();

    sei();

	float val;
	unsigned char val_timer;

	while (1) {
		/* obtener una conversion ADC desde el pin de entrada ADC 2 */
 		val = adc_get(2);

		/* linealizar el valor dado */
		val = val / 1024.0;
		val = pow(val, 0.3) * 1024.0;

		/* se redondea y se reduce a 8 bits (0 a 255) */
		val_timer = (unsigned char)(floor(val) / 4);

		/* se actualiza el tiempo de trabajo */
		timer0_set_counter(COUNTER_B, val_timer);
	}
}