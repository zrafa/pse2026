#!/bin/bash

# Antes de ejecutar, dar permisos: 'chmod +x script.sh'

DEVICE="/dev/ttyUSB0"
BAUD=9600
MAX=$(brightnessctl max)

# Configurar el puerto serie
stty -F $DEVICE $BAUD cs8 -cstopb -parenb -echo

# Leer datos del serial y cambiar brillo
while read -r value < $DEVICE; do
    brillo=$((10#$value * 50))

    # Evitamos pasarnos del maximo permitido
    if ((brillo > MAX)); then
        brillo=$MAX
    fi
    
    brightnessctl set $brillo
done