# Lab 3 — UART Serial

En este laboratorio se desarrollan tres proyectos en los que se implementa un driver para UART.

---

## Tp Serial

El primer proyecto consiste en una prueba para verificar el funcionamiento del driver. Para ello, se implementaron los siguientes métodos:

- **`serial_init`**  
  Realiza las configuraciones necesarias para el correcto funcionamiento del driver.

- **`serial_put_char`**  
  Envía un carácter para ser transmitido mediante el driver serial.

- **`serial_get_char`**  
  Espera la recepción de un dato y lo devuelve al llamador.

Además, se desarrolló un programa de prueba:

- Envía el mensaje "start\r\n" carácter a carácter.  
- Luego, queda a la espera de entrada del usuario de forma indefinida.  
- Muestra los caracteres recibidos hasta presionar <kbd>q</kbd>.

### Cómo ejecutar

Para probar este proyecto, es necesario tener instalado `cutecom`, configurado a **9600 bps** y conectado al dispositivo correspondiente.

1. Posicionarse en la carpeta del proyecto:
   ```bash
   cd tp-serial
   ```

2. Conectar el chip y ejecutar:
   ```bash
   make clean
   make
   make flash
   ```

3. Abrir `cutecom`, presionar <kbd>open</kbd> y comenzar las pruebas.  
   Desde la misma aplicación se pueden enviar datos al dispositivo.

---

## Pianito

El segundo proyecto consiste en la implementación de un piano. Este recibe entradas desde el teclado de la computadora y reproduce una determinada nota en un speaker dependiendo del caracter que reciba.

### Mapeo de teclas

- <kbd>a</kbd> → **do**  
- <kbd>s</kbd> → **re**  
- <kbd>d</kbd> → **mi**  
- <kbd>f</kbd> → **fa**  
- <kbd>g</kbd> → **sol**  
- <kbd>h</kbd> → **la**  
- <kbd>j</kbd> → **si**

### Cómo ejecutar

1. Conectar un speaker (al pin *PB0*).

2. Posicionarse en la carpeta:
   ```bash
   cd pianito
   ```

3. Conectar el chip y ejecutar:
   ```bash
   make clean
   make
   make flash
   ```

Además, se incluye el script `tomar_pulsaciones_teclado.c`, que se utiliza para enviar caracteres sin necesidad de presionar *Enter*, utilizando el modo *raw* de la terminal.

Para utilizarlo:

```bash
gcc tomar_pulsaciones_teclado.c -o tomar_pulsaciones_teclado
./tomar_pulsaciones_teclado
```

---

## Space Invaders

En este proyecto se implementa la conexión del juego Space Invaders mediante pulsadores conectados al chip.

### Controles principales

- *Mover a izquierda* → PB0  
- *Mover a derecha* → PB1  
- *Disparar* → PB2  
- *Salir del juego* → PB3  

### Modo de ejecución

1. Posicionarse en la carpeta del juego:
   ```bash
   cd juego
   ```

2. Conectar los pulsadores y el chip, luego ejecutar:
   ```bash
   make clean
   make
   make flash
   ```

3. Ejecutar el juego:

   ```bash
   cd /invaders-masters
   make
   ./invaders
   ```

La versión del juego almacenada en este directorio está modificada para recibir las pulsaciones desde el dispositivo serial y no desde el teclado.