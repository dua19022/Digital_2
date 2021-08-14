# Código de ejemplo AdafruitIO
# Universidad del Valle de Guatemala
# IE3027 - Electrónica Digital 2
# Diego Morales

# Adafruit IO
# https://io.adafruit.com/

# if Module not Found. Open Terminal/CMD and execute:
# pip3 install Adafruit_IO

from Adafruit_IO import Client, RequestError, Feed

ADAFRUIT_IO_KEY = "aio_PURz64S6H5eGl9BxCcYHtL2GVi6K"
ADAFRUIT_IO_USERNAME = "marcoaduartec"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

#Sensor 01 Feed
digital_feed = aio.feeds('sensor01') # Se selecciona el feed al que se le manda datos 
aio.send_data(digital_feed.key, 35)  # Se manda el dato deseado en el segundo lugar
digital_data = aio.receive(digital_feed.key)    # esta parte es para recibir datos
print(f'digital signal: {digital_data.value}')

#Sensor 02 Feed
analog_feed = aio.feeds('sensor02')
aio.send_data(analog_feed.key, 5)
analog_data = aio.receive(analog_feed.key)
print(f'analog signal: {analog_data.value}')

# Read data Feed
send_feed = aio.feeds('send')
aio.send_data(send_feed.key, 155)
send_data = aio.receive(send_feed.key)
print(f'send signal: {send_data.value}')
