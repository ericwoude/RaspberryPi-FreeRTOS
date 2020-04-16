#!/usr/bin/env python3

"""
Author:         Eric van der Woude
Description:    This file reads serial input and prints the message in the terminal.

Use command 'dmesg' to find the port of the FDTI device.
"""

import time
import serial

ser = serial.Serial(
        port='/dev/ttyUSB0',
        baudrate = 115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=1
)

while True:
        message = ser.readline().decode('utf-8').rstrip()
        print(message)