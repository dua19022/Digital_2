# Código de ejemplo AdafruitIO
# Universidad del Valle de Guatemala
# IE3027 - Electrónica Digital 2
# Diego Morales

# Adafruit IO
# https://io.adafruit.com/

# if Module not Found. Open Terminal/CMD and execute:
# pip3 install Adafruit_IO

from Adafruit_IO import Client, RequestError, Feed
from time import sleep
import serial
import time

# Enviar dato 
def enviar():
    time.sleep(0.01)
    puerto.write(cent)
    time.sleep(0.01)
    puerto.write(dece)
    time.sleep(0.01)
    puerto.write(unit)


envio = 184     #dato que viene desde la pág
nulo = 0        #valor nulo
nulo = str(nulo)#char nulo
temporal1 = 0
temporal2 = 0

ADAFRUIT_IO_KEY = "aio_hMsz05qOzCOZNWzatUhVHy1kdQH5"
ADAFRUIT_IO_USERNAME = "marcoaduartec"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

puerto = serial.Serial("COM2",9600)
puerto.timeout = 3
time.sleep(1)

print('Port successfully opened... \n')


Sensor01_feed = aio.feeds('sensor01')
Send_feed = aio.feeds('send')

puerto.write(b'a')
print('Sending....')
centenas = puerto.readline(1).decode("ascii")
decenas = puerto.readline(1).decode("ascii")
unidades = puerto.readline(1).decode("ascii")
contador_b = int(centenas+decenas+unidades)
print('Retrieving data...')
aio.send_data(Sensor01_feed.key, contador_b)

Send_data = aio.receive(Send_feed.key)

bitcount = Send_data.value
cent = bitcount[0:1].encode('ascii', 'ignore')
dece = bitcount[1:2].encode('ascii', 'ignore')
unit = bitcount[2:3].encode('ascii', 'ignore')
enviar()    # Se mandan los datos
print(bitcount)

    
print('Operation successful...')


