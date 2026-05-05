#!/bin/bash

DEVICE="/dev/ttyUSB0"
BAUD=9600
MAX=$(brightnessctl m)

# 1. Configuración robusta del puerto
stty -F $DEVICE $BAUD cs8 -cstopb -parenb -echo raw

echo "Escuchando en $DEVICE... (Ctrl+C para salir)"

# 2. Abrir el dispositivo como un Descriptor de Archivo (FD)
# Esto mantiene el puerto abierto permanentemente durante el script
exec 3< "$DEVICE"

# 3. Leer desde el Descriptor de Archivo 3
while read -u 3 -r value; do
    # Limpiar caracteres invisibles (\r o espacios)
    clean_value=$(echo "$value" | tr -cd '0-9')

    # Verificar que no esté vacío para evitar errores matemáticos
    if [ -n "$clean_value" ]; then
        # Usamos 10# para forzar base decimal y evitar problemas con ceros a la izquierda
        brillo=$((10#$clean_value * 50))

        if ((brillo > MAX)); then
            brillo=$MAX
        fi
        
        echo "Valor: $clean_value -> Brillo: $brillo"
        brightnessctl s $brillo
    fi
done

# 4. Cerrar el FD al terminar (opcional, se cierra al salir el script)
exec 3<&-