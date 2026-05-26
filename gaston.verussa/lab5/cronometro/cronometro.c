#include "timer.h"

void init_cronometro()
{
   init_timer();
}

char get_minutos()
{
   return (char) (get_timer() / 6000);
}

char get_segundos()
{
   return (char) ((get_timer() / 100) % 60);
}

char get_centesimas()
{
   return (char) (get_timer() % 100);
}
