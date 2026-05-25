#include "timer.h"

void cronometro_init(){
    init_timer();

}
int get_centesimas(){
   return get_timer(); 
}

int get_minutos(){
    long long centesimas_totales = get_timer();

    return (centesimas_totales/100)/60;
}

int get_segundos(){
    long long centesimas_totales = get_timer();

    return centesimas_totales/100;
}
