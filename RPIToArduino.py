#make sure the pySerial is installed on RPI
#to check the device use 'lsusb' or ls /dev/tty*

import serial
ser = serial.Serial('/dev/ttyACM0',9600);
# serial.write take a input of 4 digit string 
# first digit 0 is go forward 1 is backward 2 is Counter-Clock rotate 3 is clockwise
# other three digit is function dependent parameter
serial.write('1234');
