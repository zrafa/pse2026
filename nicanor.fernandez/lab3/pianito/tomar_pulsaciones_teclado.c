#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


struct termios original_getty;

// Restaura la terminal a su estado original
void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_getty);
}

int main() {
    int fd;
    char c;
    struct termios tio;

    // 1. Abrir el puerto serial
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("Error al abrir /dev/ttyUSB0");
        return 1;
    }

    // 2. Configurar el puerto serial (9600 8N1)
    tcgetattr(fd, &tio);
    cfsetospeed(&tio, B9600);
    cfsetispeed(&tio, B9600);
    tio.c_cflag = (tio.c_cflag & ~CSIZE) | CS8;
    tio.c_cflag |= (CLOCAL | CREAD);
    tio.c_cflag &= ~(PARENB | CSTOPB);
    tio.c_lflag = 0; // Modo raw para el puerto
    tcsetattr(fd, TCSANOW, &tio);

    // 3. Configurar la terminal (stdin) para lectura instantánea
    tcgetattr(STDIN_FILENO, &original_getty); // Guardar estado actual
    atexit(restore_terminal);                 // Asegurar que se restaure al salir

    struct termios raw = original_getty;
    raw.c_lflag &= ~(ICANON | ECHO);          // Desactivar buffer de línea y eco
    raw.c_cc[VMIN] = 1;                       // Leer de a 1 caracter
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);

    printf("Modo instantáneo activo. Presioná 'ESC' para salir.\n");

    // 4. Bucle de transmisión
    while (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == 27) break; // Salir con la tecla Escape

        if (write(fd, &c, 1) < 0) {
            perror("Error al escribir en el puerto");
            break;
        }
        
        // Opcional: imprimir qué byte enviamos para debug
        // printf("Enviado: 0x%02X\n", (unsigned char)c);
    }

    close(fd);
    return 0;
} 

/* /* Programa para enviar caracteres sin presionar enter cada vez 
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
} */