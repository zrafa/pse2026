
/* Enciende y apaga un led conectado al puerto B bit 5 de un atmega328 */

/* 
 * El puerto B de un atmega328 tiene los bits 0-5 mapeados a los 
 * pines 8-13 de arduino 
 */

#include "utils.h"

#define DO   4186
#define RE   4699
#define MI   5274
#define FA   5587
#define FA_SOS 5920
#define SOL  6272
#define LA   7040
#define SI   7902
#define DURACION_NOTA 100

typedef struct {
    int note;
    int duration;
} Note;


Note lavender[] = {
	{DO, DURACION_NOTA}, 	{SOL, DURACION_NOTA},
	{SI, DURACION_NOTA}, 	{FA_SOS, DURACION_NOTA}
};
/*
Note lavender[] = {
    {MI, 300}, {FA, 300}, {SOL, 400}, {FA, 300},
    {MI, 300}, {RE, 300}, {DO, 400}, {RE, 300},

    {MI, 300}, {FA, 300}, {SOL, 400}, {LA, 400},
    {SOL, 300}, {FA, 300}, {MI, 400}, {RE, 300},

    {MI, 300}, {FA, 300}, {SOL, 400}, {FA, 300},
    {MI, 300}, {RE, 300}, {DO, 400}, {RE, 300},

    {MI, 300}, {SOL, 400}, {LA, 400}, {SI, 500},
    {LA, 400}, {SOL, 300}, {FA, 300}, {MI, 600}
};
*/

int main(void)
{
	piezo_init();

	while (1) {
		for(short i = 0; i <= 3; i++)
		{
			tocar_nota(lavender[i].note,lavender[i].duration);
		}
    	}
}

