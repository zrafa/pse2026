# Lab 5 — Timers

En este laboratorio se desarrollan cuatro proyectos en los que se implementa un driver para distintos timers (*timer1* y *timer2*), utilizandose para diversos usos.

---

## Cronómetro

El primer proyecto consiste en probar el buen funcionamiento del driver de un timer, el cual generará interrupciones cada cierto tiempo llevando un contador que indica la cantidad de centécimas de segundo que pasaron. De esta manera se podrá observar un cronómetro en tiempo real mostrando minutos, segundos y centécimas

### Cómo ejecutar

1. Posicionarse en la carpeta del proyecto:
```bash
cd cronometro
```

2. Conectar el chip y ejecutar:
```bash
make clean
make
make flash
```

3. Ejecutar el script del archivo **lector_cronometro.c** para visualizar el cronómetro
```bash
# Compilar
gcc -o lector_cronometro lector_cronometro.c
# Ejecutar
./lector_cronometro
```

## Rotación Servo

El segundo proyecto consiste en el uso de un knob (o perilla) para controlar un servo, que es capaz de girar un rango total de 180 grados, dependiendo de donde esté posicionado el knob.

### Cómo ejecutar

1. Conectar el knob (al pin *A2*) y el servo (al pin *PB1*)

2. Posicionarse en la carpeta:
```bash
cd rotacion-servo
```

3. Conectar el chip y ejecutar:
```bash
make clean
make
make flash
```

## Motor knob

El tercer proyecto consiste en el uso de un knob (o perilla) para controlar la velocidad en la que gira un motor. A su vez, controlará la potencia de una luz led.

### Cómo ejecutar

1. Conectar el knob (al pin *A2*), un motor (al pin *PB3*) y una luz led (al pin *PD3*)

2. Posicionarse en la carpeta:
```bash
cd motor-knob
```

3. Conectar el chip y ejecutar:
```bash
make clean
make
make flash
```

## Reproductor WAV

Este proyecto consiste en la reproducción de un archivo .wav (transformado a binario) utilizando un parlante.

Se debe tener instalado **ffmpeg** para poder realizar la traducción de un archivo wav a binario.

### Cómo ejecutar

1. Conectar la salida de audio al pin *PB1*

2. Posicionarse en la carpeta:
```bash
cd reproductor-wav
```

3. Tener un archivo de audio .wav y ejecutar
```bash
ffmpeg -i nombre_archivo.wav -ac 1 -ar 11025 -f u8 salida.raw
```

4. Conectar el chip y ejecutar:
```bash
make clean
make
make flash
```

5. Ejecutar el script del archivo **send_wav.c** para enviarle al chip el archivo de audio
```bash
# Compilar
gcc -o send_wav send_wav.c
# Ejecutar
./send_wav salida.raw
```