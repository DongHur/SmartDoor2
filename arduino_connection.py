import serial 

# Reading from Arduino
arduinoSerialData = serial.Serial('/dev/ttyACM0',9600)
while 1:
   if(arduinoSerialData.inWaiting()>0):
      myData = arduinoSerialData.readline()
      print myData

# python arduino_connection.py

# Writing to Arduino
arduinoSerialData = serial.Serial('/dev/ttyACM0',9600)
arduinoSerialData.write('5')
arduinoSerialData.write('3')

# https://www.meccanismocomplesso.org/en/controlling-arduino-raspberry-pi/