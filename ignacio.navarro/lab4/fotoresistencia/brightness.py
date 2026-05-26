import serial
import subprocess
import time

try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    print("Control de brillo automático INICIADO")
except:
    print("Error abriendo el puerto.")
    exit()

def set_brightness(percentage):
    """Ejecuta el comando brightnessctl set X%"""
    try:
        subprocess.run(["brightnessctl", "set", f"{percentage}%"], check=True)
    except Exception as e:
        print(f"Error al cambiar el brillo: {e}")

while True:
    try:
        if ser.in_waiting > 0:
            # leer valor del adc (readline porque agregamos \n en el)
            linea = ser.readline().decode('utf-8').strip()
            
            if linea.isdigit():
                val_adc = int(linea)
                
                # 0-1023 ADC -> 0%-100% brillo
                porcentaje = int((val_adc / 1023) * 95) + 5
                
                print(f"Luz Ambiente: {val_adc} | Ajustando brillo a: {porcentaje}%")
                set_brightness(porcentaje)
                
    except KeyboardInterrupt:
        print("\nSaliendo...")
        break
    except Exception as e:
        print(f"Error: {e}")
    
    time.sleep(0.1)

ser.close()