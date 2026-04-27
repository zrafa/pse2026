/**********************************************************************
 *
 * main.c - the main program test file for the serial driver
 *
 **********************************************************************/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"  

int main(void) {
    serial_init(); 

    //Pines D2 (Izq) , D3 (Der) y D4 (Q) y D5 ENTER
    DDRD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5));
    
    // 3. Activamos las resistencias Pull-Up internas
    PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4)| (1 << PD5);

    // Variables para recordar cómo estaban los botones hace un instante
    int izq_ant = 1; 
    int der_ant = 1;
    int q_ant = 1;
    int enter_ant = 1;

    while (1) {
        // Leemos el estado de los 4 botones
        int izq_act = (PIND & (1 << PD2)) ? 1 : 0;
        int der_act = (PIND & (1 << PD3)) ? 1 : 0;
        int q_act = (PIND & (1 << PD4)) ? 1 : 0; 
        int enter_act = (PIND & (1 << PD5)) ? 1 : 0; 

        // --- IZQUIERDA ---
        if (izq_ant == 1 && izq_act == 0) serial_put_char('I'); 
        if (izq_ant == 0 && izq_act == 1) serial_put_char('i'); 

        // --- DERECHA ---
        if (der_ant == 1 && der_act == 0) serial_put_char('D'); 
        if (der_ant == 0 && der_act == 1) serial_put_char('d'); 

        // --- BOTÓN Q ---
        if (q_ant == 1 && q_act == 0) serial_put_char('Q'); 
        if (q_ant == 0 && q_act == 1) serial_put_char('q'); 

        // --- BOTÓN ENTER ---
        if (enter_ant == 1 && enter_act == 0) serial_put_char('E'); 
        if (enter_ant == 0 && enter_act == 1) serial_put_char('e'); 

        // Actualizamos las memorias
        izq_ant = izq_act;
        der_ant = der_act;
        q_ant = q_act;
        enter_ant = enter_act;

        _delay_ms(10); 
    }
    return 0;
}