#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include <signal.h>

#define DEVICE "/dev/ttyUSB0"

void cleanup(int sig)
{
    (void)sig;

    /* Restaurar la terminal por completo al salir */
    printf("\033[0m");    // Resetear colores y atributos de texto
    printf("\033[?25h");   // Volver a mostrar el cursor obligatoriamente
    printf("\033[2J");     // Limpiar la pantalla para borrar el cronómetro central
    printf("\033[H");      // Mover el cursor a la esquina superior izquierda (0,0)

    fflush(stdout);
    exit(0);
}

void dibujar_cronometro(const char *tiempo)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    const char *top = "+----------------------------+";
    int box_width = strlen(top);
    int box_height = 6;

    int fila = (w.ws_row - box_height) / 2;
    int columna = (w.ws_col - box_width) / 2;

    if (fila < 0)
        fila = 0;

    if (columna < 0)
        columna = 0;

    /* Posicionamos el cursor de manera absoluta y sobrescribimos */
    printf("\033[%d;%dH", fila + 1, columna + 1);
    printf("+----------------------------+");
    
    printf("\033[%d;%dH", fila + 2, columna + 1);
    printf("|         CRONOMETRO         |");

    printf("\033[%d;%dH", fila + 3, columna + 1);
    printf("|                            |");

    printf("\033[%d;%dH", fila + 4, columna + 1);
    printf("|          %8s          |", tiempo);

    printf("\033[%d;%dH", fila + 5, columna + 1);
    printf("|                            |");

    printf("\033[%d;%dH", fila + 6, columna + 1);
    printf("+----------------------------+");

    fflush(stdout);
}

int main()
{
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

    signal(SIGINT, cleanup);
    signal(SIGTERM, cleanup);

    /* Preparación inicial de la pantalla */
    printf("\033[2J");   // Limpiar la pantalla completa antes de empezar
    printf("\033[H");    // Enviar cursor al inicio (0,0)
    printf("\033[?25l"); // Ocultar el cursor por completo
    fflush(stdout);

    char c;
    char buffer[16];
    int idx = 0;

    while (1) {
        if (read(fd, &c, 1) > 0) {
            if (c == '\n') {
                buffer[idx] = '\0';
                
                /* Dibujar encima de la posición fija */
                dibujar_cronometro(buffer);
                
                idx = 0;
            } else if (idx < (int)sizeof(buffer) - 1) {
                /* Filtramos caracteres de control innecesarios */
                if (c >= 32 && c <= 126) {
                    buffer[idx++] = c;
                }
            }
        }
    }

    return 0;
}