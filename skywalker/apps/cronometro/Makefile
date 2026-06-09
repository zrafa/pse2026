CC=avr-gcc
OBJETOS=gpio.o timer0.o serial.o main.o
APP=cronometro
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p 
LDFLAGS=-mmcu=atmega328p
FIRMWARE=imagen.hex
DRIVERS=gpio timer0 serial

# Ruta base de los drivers (relativa al makefile)
DRIVERS_BASE=../..

# Archivos fuente de los drivers (copiados localmente)
DRIVER_SRCS=$(addsuffix .c, $(DRIVERS))
DRIVER_HDRS=$(addsuffix .h, $(DRIVERS))
DRIVER_OBJS=$(addsuffix .o, $(DRIVERS))
OBJETOS=$(DRIVER_OBJS) main.o

# $@:Se sustituye por el nombre del objetivo de la presente regla.
# $*:Se sustituye por la raíz de un nombre de fichero.
# $<:Se sustituye por la primera dependencia de la presente regla.
# $^:Se sustituye por una lista separada por espacios de cada una de las dependencias de la presente regla.

all: copy_drivers
	$(MAKE) build

# Copia los .c y .h de cada driver a la carpeta actual
copy_drivers:
	$(foreach drv, $(DRIVERS), \
		cp $(DRIVERS_BASE)/$(drv)/$(drv).c . ; \
		cp $(DRIVERS_BASE)/$(drv)/$(drv).h . ; \
	)

build: $(APP)

$(APP): $(OBJETOS)
	$(CC) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

flash:
	avr-objcopy -O ihex -R .eeprom $(APP) $(FIRMWARE)
	avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -D -U flash:w:$(FIRMWARE):i
	
clean:
	rm -f $(OBJETOS) $(APP) $(FIRMWARE) $(DRIVER_SRCS) $(DRIVER_HDRS)