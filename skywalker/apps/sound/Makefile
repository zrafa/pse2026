MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy

CFLAGS = -Wall -g -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I../../serial -I../../timer_1

SRCS = main.c ../../serial/serial.c ../../timer_1/timer1.c
OBJS = $(SRCS:.c=.o)
TARGET = sound

all: $(TARGET).hex

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex