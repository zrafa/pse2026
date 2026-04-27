## Descripción

En este laboratorio se encendió el **LED integrado** del Arduino y se conectaron varios LEDs externos para simular el efecto **Knight Rider**, generando un barrido de luces secuencial de ida y vuelta.

## Conexiones

- Conectar **5 LEDs** desde los pines **PB0 a PB4** (puerto B). 
  *(Nota: El código utiliza 5 estados en binario).*

## Uso

1. Requisitos:
   - Herramientas necesarias:
     - make
     - avr-gcc
     - avrdude
   - Conectar el Arduino al puerto serie y asegurarse de que esté **libre y sin uso por otras aplicaciones**.

2. Compilar y flashear el firmware:
   ```bash
   make && make flash