#!/usr/bin/env python

import serial
import serial.tools.list_ports
import sys

if __name__ == '__main__':

    availablePorts = serial.tools.list_ports.comports()

    if len(sys.argv) < 2:
        if len(availablePorts) == 0:
            print('No port found.')
            sys.exit(1)
        elif len(availablePorts) == 1:
            port = availablePorts[0]
        else:
            print('Please specify name among:')
            print('{:20s} : {:20s} {:20s}'.format('NAME', 'DEVICE', 'DESCRIPTION'))
            for p in availablePorts:
                print('{:20s} : {:20s} {:20s}'.format(p.name, p.device, p.description))
            sys.exit(1)
    else:
        port = {p.name : p for p in availablePorts}[sys.argv[1]]

    print('Using port {}'.format(port.device))
    ser = serial.Serial(port.device)

