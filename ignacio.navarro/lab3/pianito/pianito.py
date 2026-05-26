import serial
from pynput import keyboard

# Configuración del puerto
try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=0.1)
    print("PIANITO: Conectado al Arduino en /dev/ttyUSB0")
except Exception as e:
    print(f"Error al abrir puerto: {e}")
    exit()

def on_press(key):
    try:
        if hasattr(key, 'char') and key.char in ['a', 's', 'd', 'f']:
            ser.write(key.char.encode())
            print(f"Nota enviada: {key.char}")
    except Exception as e:
        print(f"Error enviando nota: {e}")

print("PIANITO ACTIVO: presioná A, S, D, F para tocar.")

with keyboard.Listener(on_press=on_press) as listener:
    listener.join()