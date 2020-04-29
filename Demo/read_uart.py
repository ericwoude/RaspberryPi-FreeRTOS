#!/usr/bin/env python3

"""
Author:         Eric van der Woude
Description:    This file reads serial input and either prints the message in
                the terminal or prints it to a file.

Use command 'dmesg' to find the port of the FDTI device.
"""

import sys
import serial

ser = serial.Serial(
        port='/dev/ttyUSB0',
        baudrate = 115200,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS,
        timeout=None
)


def read(file):
    line = ""

    while True:
            try:
                message = ser.readline().decode('utf-8').rstrip('\n')
                if message == "":
                    print(line)

                    if file:
                        file.write(line)
                        file.write("\n")

                    line = ""
                else:
                    line += f"{message} "
            except KeyboardInterrupt:
                break

"""
    Main of the program. Print data to file if argument is given,
    else it prints data to the terminal.
"""
def main():
    file = None

    if len(sys.argv) > 1:
        file = open(sys.argv[1], 'w+')

    read(file)


if __name__ == "__main__":
    main()
