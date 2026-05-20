# Laboratorio 2 - Entrada Salida digital

A lo largo de este laboratorio se desarrollaron los programas:
- **led_toy**: muestra una imagen de 8x8 de a utilizando una columna de 8 luces led e iterando por las columnas de la imagen a una alta frecuencia para que sea posible visulizarla usando vision periferica o moviendo el dispositivo rapidamente.
- **led_toy_pulsador**: mismo programa que el anterior, implementando un pulsador que cambia la imagen que se muestra.
- **ultrasonido**: detector de distancia utilizando un sensor digital de ultrasonido.
- **melody**: reproduce la cancion 'Estrellita donde estás' en un speaker, utilizando distintas frecuencias para hacer sonar las notas adecuadas.
- **sensor_proximidad_vehicular**: tomando aspectos del ultrasonido y melody, simula el sensor de proximidad de un vehículo. Se detecta la distancia utilizando el ultrasonido, y cuando esta es menor a 30 cm, el speaker comienza a emitir un pitido, el cual se vuelve mas frecuente a medida que la distancia se hace menor.

## Modo de Ejecución

Los programas **led_toy** y **led_toy_pulsador**, utilizan 8 leds conectados a los pines PB0, PB1, PB2, PB3, PC2, PC3, PC4 y PC5. Al implementar el pulsador, este debe conectarse al pin PB4.

El proyecto **ultrasonido** utiliza un sensor digital de ultrasonido que contiene 4 pines. El correspondiente a GND se conecta a tierra, el VCC al pin de 5v, TRIG (señal de disparo) se conecta a PC4 y ECHO (señal de escucha) se conecta a PC5.

El proyecto **melody** utiliza un speaker, que se conecta por un lado a tierra y por el otro al pin PB0.

El proyecto **sensor_proximidad_vehicular** utiliza un sensor digital de ultrasonido y un speaker. El sensor digital debe conectar su pin TRIG a PB1 y ECHO a PB2, mientras que GND y VCC se conectan de la misma forma que el programa previo. Por otro lado, el speaker debe conectarse con el pin PB0.

Una vez realizadas todas las conexiones deben posicionarse en la carpeta del proyecto correspondiente

```bash
cd carpeta_proyecto
```

Luego se debe conectar el chip a la computadora para poder pasarle el programa y ejecutar

```bash
make clean
make
make flash
```
