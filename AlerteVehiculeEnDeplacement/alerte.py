import serial
import RPi.GPIO as GPIO     
import os, time
alertes
vitProp
lien
# Variables qui envoies different messages
alt = 'Alerte : ' + str(alertes) + '\n'
vitess = 'Vitesse de propagation estimee : ' + str(vitProp) + '\n'
loc = 'Location :' + str(lien) +'\n'
print(alt)
print(vitess)
print(loc)
# Activation du serial port sur l'adress 9600baud
phone = serial.Serial("/dev/ttyS0", baudrate=9600, timeout=1)
# Code pour l'envoie de message
phone.write(b'AT\r\n')
time.sleep(1)
phone.write(b'AT+CMGF=1\r\n')
time.sleep(1)
phone.write(b'AT+CNMI=2,1,0,0,0\r\n')
time.sleep(1)
phone.write(b'AT+CMGS=\<destination number phone>\r\n')
time.sleep(1)
phone.write(bytes(alt, encoding='utf=8'))
phone.write(bytes(vitess, encoding='utf=8'))
phone.write(bytes(loc, encoding='utf=8'))
time.sleep(2)
phone.write(b'\x1A') #envoi SMS
time.sleep(2)