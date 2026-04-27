# Lab 3 — UART Serial

En este laboratorio se desarrollan tres proyectos en los que se implementa un driver para UART.

---

## Testing Serial

El primer proyecto consiste en una prueba para verificar el funcionamiento del driver. Para ello, se implementaron los siguientes métodos:

- **`serial_init`**  
  Realiza las configuraciones necesarias para el correcto funcionamiento.

- **`serial_put_char`**  
  Envía un carácter para ser transmitido.

- **`serial_get_char`**  
  Espera la recepción de un dato y lo devuelve al llamador.

Además, se desarrolló un programa de prueba:

- Envía el mensaje "hello my friend" carácter a carácter.  
- Luego, queda a la espera de entrada del usuario de forma indefinida.  
- Realiza un *echo* de los caracteres recibidos hasta presionar <kbd>q</kbd>.

### Cómo ejecutar

Para probar este proyecto, es necesario tener instalado `cutecom`, configurado a **9600 bps** y conectado al dispositivo correspondiente.

1. Posicionarse en la carpeta del proyecto:
   ```bash
   cd testing-serial
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

## Piano

El segundo proyecto consiste en la implementación de un piano. Este recibe entradas desde el teclado de la computadora y reproduce la nota correspondiente.

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
   cd piano
   ```

3. Conectar el chip y ejecutar:
   ```bash
   make clean
   make
   make flash
   ```

Además, se incluye el archivo `teclado_serial.c`, que permite enviar caracteres sin necesidad de presionar *Enter*, utilizando el modo *raw* de la terminal.

Para utilizarlo:

```bash
gcc teclado_serial.c -o teclado_serial
./teclado_serial
```

---

## Tetris

En este proyecto se implementa la conexión del juego Tetris mediante pulsadores conectados al chip.

### Controles principales

- *Mover a izquierda* → PB0  
- *Mover a derecha* → PB1  
- *Rotar pieza* → PB2  
- *Dejar caer pieza* → PB3  

### Controles opcionales

- *Salir del juego* → PC0  
- *Pausar el juego* → PC1  
- *Modo boss* → PC2  
- *Guardar partida* → PC3  

### Cómo ejecutar

1. Posicionarse en la carpeta del controlador:
   ```bash
   cd tetris/controlador
   ```

2. Conectar los pulsadores y el chip, luego ejecutar:
   ```bash
   make clean
   make
   make flash
   ```

3. Ejecutar el juego:

   ```bash
   cd ../juego
   make clean
   make
   bin/release/main
   ```