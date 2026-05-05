# Laboratorio 1 - Primer sistema embebido

En este trabajo laboratorio nos adentramos en el desarrollo del primer sistema embebido, comenzando con preguntas teóricas acerca del toolchain utilizado y contiuando con pequeños programas para probar el sistema. Estos son:
- **led_blink**: un programa que prende y apaga una luz led repetidamente.
- **knight-rider**: un programa en el que se prenden y apagan 5 leds de forma coordinada imitando el siguiente comportamiento:
[!Knight Rider](https://wallpapercave.com/wp/wp3292242.gif)


## Modo de Ejecución

En el programa **led_blink**, el led que se quiera utilizar deberá estar conectado en el pin PB5 del chip.

En el programa **knight-rider** se deben usar los pines PB0, PB1, PB2, PB3 Y PB4 en este orden. Debe ser ordenado para que se visualice correctamente el efecto deseado.

Teniendo las conexiones realizadas correctamente, debemos posicionarnos en la carpeta del programa correspondiente

```bash
cd led_blink/
```
o
```bash
cd knight-rider/
```


Luego se debe conectar el chip a la computadora para poder pasarle el programa y ejecutar las siguientes instrucciones:
```bash
make clean
make
make flash
```
