#include "serial.h"
#include "adc.h"
#include "math.h"
#include "utils.h"

int main(){

    //todo esto va en el arduino!
    adc_init();

    serial_init();

    int adc=0;
    char val;
    
    char anterior_val = 0;

    double aux;

    while(1){

        adc = adc_get(2); //puerto

      //  aux = pow((double) val / 1023, (double) (1.0/3.14)); //Normalizarlo entre 0 y 1

        //aux = aux * 1023; //Psarlo a un valor grande, que no sea entre 0 y 1

        //adc = (int) aux;

        //adc = adc / 4;// >> 2; //dividido 4

        val = (char) adc;

        serial_put_char(val);

        delay_ms(200);

    }

    return 0;
}
