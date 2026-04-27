# Laboratorio 3: Comunicación Serial y Control Arcade

## Descripción
Este laboratorio se enfoca en la comunicación Serial (UART) del ATmega328P y su integración con la PC, dividido en dos proyectos:

1. **Test Serial:** Programa de prueba para el driver de comunicación. Envía la palabra "start" al iniciar y luego funciona como un "eco", devolviendo a la computadora cada carácter que recibe hasta que se ingresa la letra 'q', deteniendo la ejecución.
2. **Gamepad:** Implementación de un mando de 4 botones. El microcontrolador lee los pulsadores físicos y envía señales por el puerto serie. Un script en Python (`control.py`) intercepta estos datos en la PC y los traduce a pulsaciones de teclado reales, permitiendo jugar al videojuego *Barrier X*.
3. **Piano Serial:** Al recibir caracteres ('a' hasta 'k') por el puerto serie, el Arduino genera las notas correspondientes (DO hasta DO5) a través de un parlante.

## Conexiones

**1. Para el Test Serial:**
- No requiere hardware externo. Solo el adaptador USB a Serial conectado a la PC.

**2. Para el Control Arcade:**
- **Botón Izquierda:** Pin **D2** (PD2) conectado a GND.
- **Botón Derecha:** Pin **D3** (PD3) conectado a GND.
- **Botón Q:** Pin **D4** (PD4) conectado a GND.
- **Botón Enter:** Pin **D5** (PD5) conectado a GND.


**3. Para el Piano Serial:**
- **Parlante/Buzzer:** Conectado al pin digital 13 de Arduino.

## Uso

1. Requisitos:
- Herramientas: make, avr-gcc, avrdude.
- Para Gamepad: Python 3 con pyserial y keyboard (instalación: sudo pip3 install pyserial keyboard --break-system-packages).

2. Compilación y Flasheo:
Asegura que el Makefile incluya los objetos necesarios y apunta al main deseado:
   make && make flash

3. Ejecución (Piano y Test):
- Abrir un monitor serie (como CuteCom) a 9600 baudios y presionar teclas.

4. Ejecución (Control Arcade):
- Cerrar CuteCom y ejecutar el script con permisos de administrador:
   sudo python3 control.py

   NOTA SOBRE SUDO: Es obligatorio ejecutar el script con "sudo" porque la librería "keyboard" en Linux necesita acceso directo al hardware y al kernel para poder simular pulsaciones de teclado que afecten a todo el sistema (como el juego). Sin estos permisos, el script no podrá interceptar ni enviar las teclas.
