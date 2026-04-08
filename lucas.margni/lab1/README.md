# Laboratorio 1 - Primer sistema embebido

En el presente laboratorio se encuentran dos programas princiaples:
    * **led_blink**: contiene un bucle infinito en el que repetidamente se prende y apaga un led.
    * **knight-rider**: contiene un bucle infinito en el que se prenden y apagan 5 leds, generando un efecto en escalera, simulando que hay una sección de luz que se mueve a través de los leds.

Además, se encuentran respondidas unas preguntas teóricas en archivos de texto.

## Consideraciones

En el proyecto **led_blink**, el led que se verá afectado por el código es por defecto aquel que se conecte por el pin PB5.

En el proyecto **knight-rider**, se debe conectar los cinco leds de forma ordenada para poder producir el efecto deseado. Para ello, se debe usar (en este orden) los pines PB0, PB1, PB2, PB3 Y PB4.

## Ejecución

Para probar alguno de los dos programas principales deben, en primer lugar, posicionarnos en la carpeta del programa correspondiente

```bash
cd led_blink/
```
o
```bash
cd knight-rider/
```

Luego se debe conectar el chip a la computadora para poder pasarle el programa y ejecutar
```bash
make clean
make
make flash
```