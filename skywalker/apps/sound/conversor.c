/*
 * Envía un archivo WAV a través del puerto serie.
 * Se salta los primeros 44 bytes (encabezado) y envía el audio a 115200 baudios.
 * Incluye una pausa para evitar saturar el buffer de 64 bytes del microcontrolador.
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main(int argc, char **argv)
{
	int fd;
	struct termios tty;
	FILE *audio;
	unsigned char byte;

	if (argc < 2) {
		fprintf(stderr, "Uso: %s <archivo.wav>\n", argv[0]);
		return 1;
	}

	fd = open("/dev/ttyUSB0", O_WRONLY | O_NOCTTY);
	if (fd < 0) {
		perror("Error abriendo puerto serie");
		return 1;
	}

	tcgetattr(fd, &tty);
	cfsetispeed(&tty, B115200);
	cfsetospeed(&tty, B115200);
	
	tty.c_cflag |= (CLOCAL | CREAD | CS8);
	tty.c_cflag &= ~(PARENB | CSTOPB | CSIZE | CRTSCTS);
	tty.c_lflag = 0;
	tty.c_iflag = 0;
	tty.c_oflag = 0;
	
	tcsetattr(fd, TCSANOW, &tty);

	audio = fopen(argv[1], "rb");
	if (!audio) {
		perror("Error abriendo WAV");
		return 1;
	}

	fseek(audio, 44, SEEK_SET);
	printf("Enviando audio ...\n");

	while (fread(&byte, 1, 1, audio) == 1) {
		write(fd, &byte, 1);
		usleep(125);
	}

	printf("Transmisión finalizada.\n");
	
	fclose(audio);
	close(fd);
	
	return 0;
}