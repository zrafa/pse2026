#include "utils.h"

volatile unsigned char * ddr_d    = (unsigned char *) 0x2A;
volatile unsigned char * puerto_d = (unsigned char *) 0x2B;

volatile unsigned char * ddr_b    = (unsigned char *) 0x24;
volatile unsigned char * puerto_b = (unsigned char *) 0x25;

// para pulsador
volatile unsigned char * ddr_c    = (unsigned char *) 0x27;
volatile unsigned char * puerto_c = (unsigned char *) 0x28;
volatile unsigned char * pin_c    = (unsigned char *) 0x26;

void led_toy_init() {
    // pines 2-7
    *ddr_d |= 0xFC; 
    
    // pines 8-13
    *ddr_b |= 0x3F;
}

void input_init() {
    *ddr_c &= ~0x01; 
    *puerto_c |= 0x01; 
}

int boton_presionado() {
    if (!((*pin_c) & 0x01)) { 
        delayms(10); 
        if (!((*pin_c) & 0x01)) {
            return 1;
        }
    }
    return 0;
}

void display_column(unsigned int data) {
    unsigned int bits_bajos = (data & 0x003F); 

    // mueve dos bits para no tocar los pines RX/TX
    unsigned char val_d = (unsigned char)(bits_bajos << 2);
    
    *puerto_d = (*puerto_d & 0x03) | val_d;

    unsigned int bits_altos = (data >> 6);
    
    unsigned char val_b = (unsigned char)(bits_altos & 0x3F);
    
    *puerto_b = (*puerto_b & 0xC0) | val_b;
}

/*
aprox 60 hz con
display_column(columna_a_mostrar);
    delayms(1);
}

        display_column(0);
        delayms(8);

medido con osciloscopio
*/

void delayms(int n) {
    volatile int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 840; j++); 
    }
}