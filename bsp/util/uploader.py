import time
import serial
import sys
import os


def checkPath(path):
    if not os.path.isfile(path):
        raise Exception("No such file: %s" % path)


uart = serial.Serial("/dev/ttyUSB1", baudrate=9600, parity=serial.PARITY_NONE,
                     stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)
counter = 0

checkPath(sys.argv[1])

try:
    f = open(sys.argv[1])
    for line in f:
        uart.write(b'%d' % int(line, 16))
finally:
    f.close()


# while 1:
#     uart.write(b"Write Counter: %d \n" % (counter))
#     print("printed")
#     time.sleep(1)
#     counter += 1
