#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int serial_fd = -1;

int init_serial(const char *device) {
    struct termios tty;

    // Abrir puerto serie en modo bloqueante
    serial_fd = open(device, O_WRONLY | O_NOCTTY);

    if (serial_fd < 0) {
        perror("Error opening serial");
        return -1;
    }

    // Obtener configuración actual
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("tcgetattr");
        close(serial_fd);
        return -1;
    }

    // Baudrate 115200
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    // Configuración 8N1
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;      // 8 bits
    tty.c_cflag &= ~PARENB;  // sin paridad
    tty.c_cflag &= ~CSTOPB;  // 1 stop bit
    tty.c_cflag &= ~CRTSCTS; // sin flow control

    // Modo raw
    tty.c_lflag = 0;
    tty.c_iflag = 0;
    tty.c_oflag = 0;

    // Aplicar configuración
    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(serial_fd);
        return -1;
    }

    return 0;
}

/* Envía exactamente 1 byte */
int send_byte(unsigned char byte) {
    return write(serial_fd, &byte, 1);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];

    FILE *input = fopen(input_file, "rb");

    if (!input) {
        perror("Error opening input file");
        return 1;
    }

    if (init_serial("/dev/ttyUSB0") != 0) {
        fclose(input);
        return 1;
    }

    printf("Sending file...\n");

    unsigned char byte;

    while (fread(&byte, 1, 1, input) == 1) {

        int n = send_byte(byte);

        if (n != 1) {
            perror("Error writing to serial");
            break;
        }

        // Esperar a que el byte se transmita completamente
        tcdrain(serial_fd);

        // printf("Sent byte: 0x%02X\n", byte);
    }

    printf("Transmission finished\n");

    fclose(input);
    close(serial_fd);

    return 0;
}