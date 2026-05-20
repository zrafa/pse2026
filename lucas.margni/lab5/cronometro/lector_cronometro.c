#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#define DEVICE "/dev/ttyUSB0"

int main() {

    int fd = open(DEVICE, O_RDONLY | O_NOCTTY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct termios tty;

    tcgetattr(fd, &tty);

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_oflag &= ~OPOST;

    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    tcsetattr(fd, TCSANOW, &tty);

    char c;
    char buffer[16];

    int idx = 0;
    int ultimo_largo = 0;

    while (1) {

        if (read(fd, &c, 1) > 0) {

            if (c == '\n') {

                buffer[idx] = '\0';

                int largo = strlen(buffer);

                // volver al inicio
                printf("\r");

                // imprimir nuevo valor
                printf("%s", buffer);

                // borrar sobrantes
                for (int i = largo; i < ultimo_largo; i++) {
                    putchar(' ');
                }

                // volver al inicio nuevamente
                printf("\r");

                fflush(stdout);

                ultimo_largo = largo;
                idx = 0;
            } else {

                if (idx < sizeof(buffer) - 1) {
                    buffer[idx++] = c;
                }
            }
        }
    }

    close(fd);
    return 0;
}