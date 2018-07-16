#!/usr/bin/env python

# require dev-python/pyserial and dev-python/pyserial-asyncio

import serial
from serial.threaded import Packetizer
import serial.tools.list_ports
import sys
import asyncio
import serial_asyncio

class Output(Packetizer):

    inputString = ''
    TERMINATOR = b'\n'
    ENCODING = 'utf-8'

    async def sendMsg(self):
        loop = asyncio.get_event_loop()
        reader = asyncio.StreamReader()
        reader_protocol = asyncio.StreamReaderProtocol(reader)
        await loop.connect_read_pipe(lambda: reader_protocol, sys.stdin)

        while True:
            data = await reader.readline()
            data = data.split(b'\n')[0]
            self.transport.writelines([data+b'\r\n'])

            data = data.decode('utf-8')
            dest,src = '??','??'
            try:
                if (len(data) > 4):
                    dest,src = int(data[0:2], base=16),int(data[2:4], base=16)
                    data = data[4:]
            except ValueError:
                pass
            print('< {:x} -> {:x} : {:s}'.format(src, dest, data))

    def connection_made(self, transport):
        print(repr(transport))
        self.transport = transport
        transport.serial.rts = False

        asyncio.get_event_loop().create_task(self.sendMsg())
        print('Communication opened:')
        print(f'\tport:       {self.transport._serial.port}')
        print(f'\tbaudrate:   {self.transport._serial._baudrate} Hz')
        print(f'\ttimeout:    {self.transport._serial._timeout}')
        print(f'\tbytesize:   {self.transport._serial._bytesize}')
        print(f'\tparity:     {self.transport._serial._parity}', end='\n\n')

    def handle_packet(self, data):
        data = data.decode('utf-8')
        dest,src = '??','??'
        try:
            if (len(data) > 4):
                dest,src = int(data[0:2], base=16),int(data[2:4], base=16)
                data = data[4:]
        except ValueError:
            pass
        print('> {:x} -> {:x} : {:s}'.format(src, dest, data))


    def connection_lost(self, exc):
        print('port closed')
        asyncio.get_event_loop().stop()

    def pause_writing(self):
        print('pause writing')
        print(self.transport.get_write_buffer_size())

    def resume_writing(self):
        print(self.transport.get_write_buffer_size())
        print('resume writing')

if __name__ == '__main__':

    availablePorts = serial.tools.list_ports.comports()

    if len(sys.argv) < 2:
        if len(availablePorts) == 0:
            print('No available port found.')
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

    loop = asyncio.get_event_loop()
    loop.create_task(serial_asyncio.create_serial_connection(loop, Output,
                                                             port.device, baudrate=9600))

    try:
        loop.run_forever()
    except KeyboardInterrupt:
        loop.close()



