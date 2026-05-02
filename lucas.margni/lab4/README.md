Ejecutar proyecto brillo-adaptable

```bash
make clean
make
make flash
```

y ejecutar el script
```bash
chmod +x script.sh
sudo ./script.sh
```

# Lab 4 — ADC

En este laboratorio se desarrollan tres proyectos en los que se implementa un driver para ADC, utilizandose para distintas funciones.

---

## Driver ADC

Se creó un driver para controla el ADC (Analog to Digital Converter) encargado de transformar una señal analógica continua en una representación digital que un microprocesador puede procesar. Para ello se generaron los métodos:

- **`adc_init`**
  Realiza las configuraciones iniciales necesarias para el correcto funcionamiento.

- **`adc_get`**
  Recibe un *char* correspondiente a la entrada análoga por donde ingresarán datos y espera la recepción de un dato para devolverlo al llamador.

## Brillo Adaptable

El primer proyecto consiste en utilizar un sensor que detecta la intensidad de luz que recibe, llamada fotoresistencia o LDR. Dependiendo de cuanta luz detecte, modificará el brillo de la pantalla de la computadora.

Para ello usa la aplicación **brightnessctl**, por lo que se necesita tenerla instalada para probar el proyecto

### Cómo ejecutar

Se debe conectar una fotoresistencia por el pin de entrada ADC2, es decir el etiquetado como **A2**.

1. Posicionarse en la carpeta del proyecto:
```bash
cd brillo-adaptable
```

2. Conectar el chip y ejecutar:
```bash
make clean
make
make flash
```

3. Ejecutar el script disponible en la carpeta para utilizar brightnessctl
```bash
# Dar permisos al script
chmod +x script.sh
# Ejecutar con superusuario
sudo ./script.sh
```

## Knob Speaker

El segundo proyecto consiste en el uso de un knob (o perilla) la cual variará qué tan agudo sale el sonido por un speaker.

### Cómo ejecutar

1. Conectar un speaker (al pin *PB0*) y el knob (al pin *A2*)

2. Posicionarse en la carpeta:
```bash
cd knob-speaker
```

3. Conectar el chip y ejecutar:
```bash
make clean
make
make flash
```

## Juego SDL Ball

En este proyecto se implementa la conexión del juego SDL ball mediante un knob (encargado del movimiento) y un pulsador (para el disparo de la pelota) conectados al chip.

### Cómo ejecutar

1. Posicionarse en la carpeta del controlador:
```bash
cd sdl-ball/controlador
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
make
./sdl-ball
```