#include "timer.h"

void cronometro_init(){
    init_timer();

}
char get_centesimas(){
   return  (char) (get_timer() % 100); 
}

char get_minutos(){
    long long centesimas_totales = get_timer();

    return (char) (centesimas_totales/100)/60;
}

char get_segundos(){
    long long centesimas_totales = get_timer();

    return (char) ((centesimas_totales/100) % 60);
}
