
MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/ttyUSB0
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Wall

all: main.hex

main.elf: main.o serial.o timer1.o
	$(CC) $(CFLAGS) -o main.elf main.o serial.o timer1.o

main.o: main.c serial.h timer1.h
	$(CC) $(CFLAGS) -c main.c

serial.o: serial.c serial.h
	$(CC) $(CFLAGS) -c serial.c

timer1.o: timer1.c timer1.h
	$(CC) $(CFLAGS) -c timer1.c

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom main.elf main.hex

clean:
	rm -f *.o *.elf *.hex

flash: main.hex
	$(AVRDUDE) -v -c arduino -p $(MCU) -P $(PORT) -b 115200 -D -U flash:w:main.hex:i
