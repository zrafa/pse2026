void thread_pse(controllerClass& control) {
  // abrir puerto
  int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
  if (fd == -1) {
    std::cerr << "No se pudo abrir /dev/ttyUSB0" << std::endl;
    return;
  }

  char buf[64];
  while (1) {
    // leer datos del arduino
    int n = read(fd, buf, sizeof(buf) - 1);
    if (n > 0) {
      buf[n] = '\0';
      int pos_arduino, boton;

      // parsear datos
      if (sscanf(buf, "%d %d", &pos_arduino, &boton) == 2) {
        // calculo para hacer convertir de 0-1023 a datos del juego -1.66 a 1.66
        float px = (pos_arduino / 1023.0f) * -3.32f + 1.66f;
        control.movePaddle(px);

        if (boton == 1) {
          control.btnPress();  // dispara
        }
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  close(fd);
}