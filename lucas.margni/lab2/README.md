# Laboratorio 1 - Entrada Salida digital

A lo largo de este laboratorio se desarrollaron los programas:
- **led_toy**: muestra una imagen de 8x8 de a columnas utilizando luces led, a una alta frecuencia para que sea posible visulizarla usando vista periferica o moviendo el dispositivo.
- **led_toy_pulsador**: mismo programa que el anterior, con el agregado de un pulsador que cambia la imagen que se muestra.
- **ultrasonido**: detector de distancia utilizando un sensor digital.
- **melody**: utilizando un speaker, produce la cancion 'estrellita' con las notas adecuadas.
- **sensor_proximidad_vehicular**: tomando aspectos del ultrasonido y melody, es un programa que simula el sensor de marcha atras de un vehiculo. Utilizando el ultrasonido detectamos la distancia, y cuando esta es menor a 30 cm, se empieza a escuchar un pitido, el cual sera mas frecuente a medida que la distancia sea menor.

## Consideraciones

Los proyectos **led_toy** y **led_toy_pulsador**, utilizan 8 leds conectados (en este orden) a los pines PB0, PB1, PB2, PB3, PC2, PC3, PC4 y PC5. A se vez, en el caso de tener un pulsador, debe conectarse al pin PB4.

El proyecto **ultrasonido** utiliza un sensor digital de ultrasonido que contiene 4 pines. El correspondiente a GND se conecta a tierra, el VCC al pin de 5v que viene en el pin, TRIG a PC4 y ECHO a PC5.

El proyecto **melody** utiliza un speaker, que debe ser conectado por un lado a tierra y por el otro al pin PB0.

El proyecto **sensor_proximidad_vehicular** utiliza un sensor digital de ultrasonido y un speaker. El sensor digital debe conectar su pin TRIG a PB1 y ECHO a PB2. Por otro lado, el speaker debe conectarse con el pin PB0.

## Ejecución

Para probar cualquiera de los programas principales deben, en primer lugar, posicionarse en la carpeta del proyecto correspondiente

```bash
cd carpeta_proyecto
```

Luego se debe conectar el chip a la computadora para poder pasarle el programa y ejecutar

```bash
make clean
make
make flash
```
