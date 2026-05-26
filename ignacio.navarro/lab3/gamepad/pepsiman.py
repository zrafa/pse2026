import serial
from pynput.keyboard import Controller, Key
import time

# configuracion del puerto
try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.1)
    print("GAMEPAD: Conectado al Arduino en /dev/ttyUSB0")
except Exception as e:
    print(f"Error al abrir puerto: {e}")
    exit()

kb = Controller()

gamepad_map = {
    'A': 'a',  'a': 'a', # izquierda
    'D': 'd',  'd': 'd', # derecha
    'K': 'k',  'k': 'k', # salto
    'J': 'j',  'j': 'j'  # deslizar
}

def check_arduino():
    if ser.in_waiting > 0:
        # leer bytes
        data = ser.read(ser.in_waiting).decode('utf-8', errors='ignore')
        for char in data:
            if char in gamepad_map:
                key = gamepad_map[char]
                if char.isupper():
                    kb.press(key)
                    # print(f"Gamepad: Presionando {key}")
                else:
                    kb.release(key)
                    # print(f"Gamepad: Soltando {key}")

print("GAMEPAD ACTIVO: Usa los pulsadores del Arduino para jugar Pepsiman.")
print("Presiona Ctrl+C para salir.")

try:
    while True:
        check_arduino()
        time.sleep(0.01)
except KeyboardInterrupt:
    print("\nCerrando Gamepad...")
finally:
    ser.close()