#include "utils.h"

int main(void)
{	
	led_init();

	while (1) {
		esperar();
		led_on();

		esperar();
		led_off();
    	}
}


