# read serial port
import serial
import time
ser = serial.Serial('/dev/tty.usbserial-A50285BI', 115200)
time.sleep(2)
# read serial port
while True:
    if ser.inWaiting() > 0:
        line = ser.readline()
        print(line)
        