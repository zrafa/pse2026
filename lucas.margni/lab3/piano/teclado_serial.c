/* Programa para enviar caracteres sin presionar enter cada vez */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <signal.h>
#include <sys/ioctl.h>

int serial_fd = -1;
struct termios oldt;

// Restaurar terminal y cerrar serial
void cleanup(int sig) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if (serial_fd != -1) {
        close(serial_fd);
    }

    printf("\nSaliendo...\n");
    exit(0);
}

int main() {
    struct termios newt;

    // --- Abrir puerto serie ---
    serial_fd = open("/dev/ttyUSB0", O_WRONLY | O_NOCTTY);
    if (serial_fd < 0) {
        perror("Error abriendo /dev/ttyUSB0");
        return 1;
    }

    // --- Configurar puerto serie ---
    struct termios tty;
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("tcgetattr");
        return 1;
    }

    // Modo RAW (clave)
    cfmakeraw(&tty);

    // Velocidad 9600
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    // Configuración 8N1
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    // Desactivar control de flujo por software
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Control de lectura
    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(serial_fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        return 1;
    }

    // Limpiar buffers
    tcflush(serial_fd, TCIOFLUSH);

    // --- Activar DTR y RTS (importante para algunos dispositivos) ---
    int status;
    ioctl(serial_fd, TIOCMGET, &status);
    status |= TIOCM_DTR;
    status |= TIOCM_RTS;
    ioctl(serial_fd, TIOCMSET, &status);

    // --- Configurar teclado en modo raw ---
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // sin buffer ni eco
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // --- Capturar Ctrl+C ---
    signal(SIGINT, cleanup);

    printf("Presiona teclas (Ctrl+C para salir)\n");

    // --- Loop principal ---
    while (1) {
        char c;
        if (read(STDIN_FILENO, &c, 1) > 0) {
            write(serial_fd, &c, 1);
        }
    }

    return 0;
}