#make sure the pySerial is installed on RPI
#to check the device use 'lsusb' or ls /dev/tty*

import serial
ser = serial.Serial('/dev/ttyACM0',9600);
serial.write('123');
