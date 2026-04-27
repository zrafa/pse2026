import serial
import keyboard

puerto = '/dev/ttyUSB0'
baudios = 9600

try:
    arduino = serial.Serial(puerto, baudios)
    print("Control conectado")
except Exception as e:
    print(f"Error: No se pudo conectar a {puerto}.{e}")
    exit()


while True:
    if arduino.in_waiting > 0:
        # Leemos la letra que mandó el código en C
        letra = arduino.read().decode('utf-8')
        
        # Simulamos el teclado físico
        if letra == 'I':
            keyboard.press('left')   # Apretar flecha izquierda
        elif letra == 'i':
            keyboard.release('left') 
        elif letra == 'D':
            keyboard.press('right')  # Apretar flecha derecha
        elif letra == 'd':
            keyboard.release('right')
        elif letra == 'Q':
            keyboard.press('q')   # Apretar la tecla Q
        elif letra == 'q':
            keyboard.release('q')
        elif letra == 'E':
            keyboard.press('enter')   # Apretar la tecla Enter
        elif letra == 'e':
            keyboard.release('enter')