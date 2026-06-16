MCU = atmega328p
F_CPU = 16000000UL
PORT ?= /dev/ttyUSB0
BAUD = 115200

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -Wall -g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I../../serial -I../../timer_1

SRCS = main.c ../../serial/serial.c ../../timer_1/timer1.c
OBJS = $(SRCS:.c=.o)
TARGET = sound

all: $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

flash: $(TARGET).hex
	$(AVRDUDE) -v -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -D -U flash:w:$<:i

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex