# Laboratorio 4: 

Este repositorio contiene las implementaciones de bajo nivel para el **Laboratorio 4**. El proyecto se enfoca en el desarrollo de drivers para el microcontrolador ATmega328P.

---

## Ejercicios Desarrollados

### 1. Sensor de Luz y Control de Brillo Automático.
Implementación de un sistema de lectura analógica para medir niveles de intensidad lumínica con una fotoresistencia (LDR) y ajustar dinámicamente el brillo del monitor.
* **Funcionamiento:** El microcontrolador lee constantemente el pin A0 y transmite el valor numérico por el puerto serie. En la PC, un script de Python lee estos valores, los interpola y ajusta automáticamente el brillo de la pantalla usando el comando `brightnessctl`.

### 2. Speaker-Knob.
Generador de tonos cuya frecuencia varía proporcionalmente a la entrada analógica detectada.
* **Funcionamiento:** El sistema lee el sensor en el pin A0 y ajusta dinámicamente la frecuencia de una señal enviada a un parlante conectado en el pin D13 (PB5).

### 3. Controlador para SDL-Ball.
Integración del hardware para controlar la plataforma (paddle) y el sistema de disparo del juego sdl-ball en Linux.
* **Control de Movimiento:** Un potenciómetro mapea su posición a las coordenadas de la pantalla del juego. Incluye corrección logarítmica y un filtro de media móvil exponencial (EMA) en C++ para suavizar el ruido.
* **Sistema de Disparo:** Un pulsador en el pin D8 (PB0) permite lanzar la bola.
* **Comunicación Serie:** Envío empaquetado de datos usando un protocolo de etiquetas (`'K'` para el Knob y `'B'` para el botón) hacia un hilo (`thread_pse`) en el motor C++ del juego, usando `termios.h` en modo Raw para evitar bloqueos del SO.

---

## Estructura de Drivers
* `adc.c` / `adc.h`: Driver genérico para el Conversor Analógico Digital con soporte para selección de canales y resolución configurada a 8 bits.
* `serial.c` / `serial.h`: Driver UART para comunicación por puerto serie a 9600 bps.
* `sound.c` / `sound.h`: Abstracción para la generación de frecuencias sonoras.

## Esquema de Conexión

| Componente | Pin Arduino |
| :--- | :--- |
| **Fotoresistencia / Potenciómetro** | **A0** |
| **Pulsador** | **D8 (PB0)** |
| **Parlante / Buzzer** | **D13 (PB5)** |

---

## Compilación y Ejecución

### Firmware (Arduino)
Para compilar y cargar los programas en la placa:
```bash
make
make flash


Ejecutar el juego:
```bash
cd ../juego
make
sudo ./sdl-ball
```