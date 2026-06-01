import serial
import time
import sys

PUERTO_SERIAL = '/dev/ttyUSB0' 
BAUDRATE = 115200
ARCHIVO_WAV = 'salida.wav'
SAMPLE_RATE = 11025.0


if len(sys.argv) > 1:
    ARCHIVO_WAV = sys.argv[1]
else:
    ARCHIVO_WAV = 'salida.wav'

try:
    print('Conectando con el Arduino...')
    arduino = serial.Serial(PUERTO_SERIAL, BAUDRATE, timeout=1)
    time.sleep(2) # Esperar el reseteo automático del Arduino al conectar
    
    with open(ARCHIVO_WAV, 'rb') as wav:
        # Los archivos WAV estándar tienen una cabecera de 44 bytes
        cabecera = wav.read(44)
        
        print("Reproduciendo audio en el Arduino... Presiona Ctrl+C para detener.")
        
        # Leemos el primer byte de datos de audio
        byte_audio = wav.read(1)
        
        intervalo = 1.0 / SAMPLE_RATE
        
        proximo_envio = time.time()
        
        while byte_audio:
            # Enviamos el byte binario puro al Arduino
            arduino.write(byte_audio)
            
            proximo_envio += intervalo
            tiempo_espera = proximo_envio - time.time()
            if tiempo_espera > 0:
                time.sleep(tiempo_espera)
                
            # Leer el siguiente byte del archivo
            byte_audio = wav.read(1)
            
    print("\nTransmisión finalizada con éxito.")
    arduino.close()

except FileNotFoundError:
    print(f"Error: No se encontró el archivo {ARCHIVO_WAV}. Asegúrate de correr primero el comando de ffmpeg.")
except serial.SerialException:
    print(f"Error: No se pudo abrir el puerto {PUERTO_SERIAL}. ¿Está el Arduino conectado?")
except KeyboardInterrupt:
    print("\nReproducción cancelada por el usuario.")
    if 'arduino' in locals():
        arduino.close()
