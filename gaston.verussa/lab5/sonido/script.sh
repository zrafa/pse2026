stty -F /dev/ttyUSB0 speed 115200 # o 2400 la que necesiten
cat salida2.wav >> /dev/ttyUSB0 # envía el contenido del audio al driver del dispositivo serial
