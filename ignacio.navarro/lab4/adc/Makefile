# --- Configuración del microcontrolador ---
MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/ttyUSB0

# --- Herramientas ---
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# --- Banderas de compilación ---
CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Wall

# --- Regla principal ---
all: main.hex

# --- Compilación de objetos ---
main.elf: main.o adc.o
	$(CC) $(CFLAGS) -o main.elf main.o adc.o

main.o: main.c adc.h
	$(CC) $(CFLAGS) -c main.c

adc.o: adc.c adc.h
	$(CC) $(CFLAGS) -c adc.c

# --- Creación del archivo .hex ---
main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom main.elf main.hex

# --- Regla para limpiar archivos compilados ---
clean:
	rm -f *.o *.elf *.hex

# --- Regla para subir al Arduino (flash) ---
flash: main.hex
	$(AVRDUDE) -v -c arduino -p $(MCU) -P $(PORT) -b 115200 -D -U flash:w:main.hex:i
