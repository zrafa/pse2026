
/* utils.c - funciones de soporte al programa principal */

/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328p
 * El puerto B de un atmega328p tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#define MS_ESPERA 75

/* puertos de E/S */

/* direccion de PORTB (registro de datos) */
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

/* direccion de DDR B (registro de control) */
volatile unsigned char * ddr_b = (unsigned char *) 0x24;

/* direccion PIN B (registro de datos de entrada) */
volatile unsigned char * pin_b = (unsigned char *) 0x23;

unsigned char aux_b;
unsigned int tiempo_apretado[3];
unsigned char ultimo_valor[3];

void pulsadores_init(void) {
    aux_b = (1 << 1) | (1 << 2) | (1 << 3);
    /* PB1 y PB2 como entrada */
    *ddr_b &= ~aux_b;
    /* activar pull-up interno: el pin queda en HIGH cuando no se pulsa */
    *puerto_b |= aux_b;
    tiempo_apretado[0] = 0;
    tiempo_apretado[1] = 0;
    tiempo_apretado[2] = 0;
    ultimo_valor[0] = 1;
    ultimo_valor[1] = 1;
    ultimo_valor[2] = 1;
}

/* espera 1ms */
void esperar(){
	volatile unsigned long i;
	for(int j = 0; j < MS_ESPERA; j++)
	{
		for(i = 0; i< 452;i++);
	}
}

int leer_pulsador(int num_pulsador){
	if(num_pulsador >= 0 | num_pulsador <= 2)
	{
		if(*pin_b & (1 << (num_pulsador + 1)))
		{
			tiempo_apretado[num_pulsador] = 0;
			ultimo_valor[num_pulsador] = 1;
		} else {
			if(ultimo_valor[num_pulsador])
			{
				ultimo_valor[num_pulsador] = 0;
			} else {
				tiempo_apretado[num_pulsador] += MS_ESPERA;
			}
			if(tiempo_apretado[num_pulsador] > 10)
			{
				return 1;
			}
		}
	}
	return 0;
}
