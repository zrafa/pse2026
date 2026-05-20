#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

// for new get_char
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int serial_fd = -1;

int init_serial(const char *device) {
    struct termios tty;

    serial_fd = open(device, O_RDONLY | O_NOCTTY);
    if (serial_fd < 0) {
        perror("Error opening serial");
        return -1;
    }

    // non-blocking
    //fcntl(serial_fd, F_SETFL, O_NONBLOCK);

    tcgetattr(serial_fd, &tty);

    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;     // 8 bits
    tty.c_cflag &= ~PARENB; // sin paridad
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;

    tty.c_lflag = 0; // raw mode
    tty.c_iflag = 0;
    tty.c_oflag = 0;

    tcsetattr(serial_fd, TCSANOW, &tty);

    return 0;
}

/* protocolo: leer siempre un int y despues un char */
int read_int() {
    unsigned char high, low;

    read(serial_fd, &high, 1);
    read(serial_fd, &low, 1);

    return (high << 8) | low;
}

char read_char() {
    char c;
    read(serial_fd, &c, 1);

    return c;
}

int main() {
    if (init_serial("/dev/ttyUSB0") != 0) {
        return 1;
    }

    int i;
    char c;

    while(true) {
        i = read_int();
        c = read_char();
        
        printf("int: %i\n", i);
        printf("char: %c\n", c);
    }
}