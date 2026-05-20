#include "timer2.h"
#include "serial.h"

void main() {
	char cronometro[8] = {'0', '0', ':', '0', '0', ':', '0', '0'};

	timer2_init();
	serial_init();

	while (1) {
		int val = timer2_get_ticks();

		/* centisegundos */
		int cs = val % 100;
		cronometro[7] = '0' + (cs % 10);
		cronometro[6] = '0' + (cs / 10);

		/* segundos */
		int seg = (val / 100) % 60;
		cronometro[4] = '0' + (seg % 10);
		cronometro[3] = '0' + (seg / 10);

		/* minutos */
		int min = val / 6000;
		cronometro[1] = '0' + (min % 10);
		cronometro[0] = '0' + ((min / 10) % 10);

		for(char i = 0; i < 8; i++) {
			serial_put_char(cronometro[i]);
		}
		serial_put_char('\n');
	}
}