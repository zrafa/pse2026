# Laboratorio2: Display LED, Melody y Ultrasonido

## Descripción
Este laboratorio está dividido en tres programas independientes para el control de periféricos con el microcontrolador ATmega328P:

1. Led_toy: Muestra figuras (Carita feliz, Rombo) en una matriz de 12 LEDs mediante persistencia de la visión. Utiliza un pulsador para alternar entre las diferentes imágenes.
2. Melody : Genera una escala musical (de DO4 a DO5) manipulando directamente los registros del puerto B para emitir sonido a través de un buzzer o parlante.
3. Ultrasonido : Realiza lecturas de distancia en centímetros utilizando un sensor HC-SR04 y envía los datos a la computadora mediante comunicación Serial.

## Conexiones

1. Display LED
- LEDs: 12 LEDs conectados desde el pin D2 al D13 (bits 0 al 11).
- Pulsador: Conectado a la entrada configurada para el cambio de imagen.

2. Melody
- Parlante/Buzzer: Conectado al pin PB5 (Pin digital 13 de Arduino).

3. Ultrasonido
- Sensor HC-SR04: Pines Trigger y Echo conectados según la configuración de la librería ultrasound.h.
- Puerto Serie: Conexión a la PC para visualización de datos (ej. mediante CuteCom).

## Uso

1. Requisitos
- Herramientas de desarrollo: make, avr-gcc, avrdude.
- Asegurarse de que el puerto serie esté libre y sin uso por otras aplicaciones antes de comenzar.

2. Compilación y Flasheo
Asegúrate de que el Makefile esté configurado para apuntar al archivo main que deseas probar. Luego ejecuta:
   make && make flash

3. Limpieza
Para eliminar los archivos binarios y temporales generados durante la compilación:
   make clean