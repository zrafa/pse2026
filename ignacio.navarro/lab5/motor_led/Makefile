
MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/ttyUSB0
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -Wall

all: main.hex

main.elf: main.o serial.o timer2_pwm.o adc.o
	$(CC) $(CFLAGS) -o main.elf main.o serial.o timer2_pwm.o adc.o

main.o: main.c serial.h timer2_pwm.h adc.h
	$(CC) $(CFLAGS) -c main.c

serial.o: serial.c serial.h
	$(CC) $(CFLAGS) -c serial.c

adc.o: adc.c adc.h
	$(CC) $(CFLAGS) -c adc.c

timer2_pwm.o: timer2_pwm.c timer2_pwm.h
	$(CC) $(CFLAGS) -c timer2_pwm.c

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom main.elf main.hex

clean:
	rm -f *.o *.elf *.hex

flash: main.hex
	$(AVRDUDE) -v -c arduino -p $(MCU) -P $(PORT) -b 115200 -D -U flash:w:main.hex:i
