#!/usr/bin/env python

import configtools
from os.path import abspath, join, dirname, pardir 
from pprint import pformat

SYSTEM_DIR  = abspath(dirname(__file__))
SYSTEM_FILENAME = 'main.system'
LOGMSG_H_FILENAME = 'logmsg.h'
COMMANDS_H_FILENAME = 'commands.h'
PROTOCOL_H_FILENAME = 'protocol.h'
DEVICE_H_FILENAME = 'device.h'


def write_libslogmsg(system):

    # write header files
    for lib in system.libraries.values():
        with open(join(lib.path, LOGMSG_H_FILENAME), 'w') as f:
            configtools.writeHeader(f, mode='C')
            configtools.writePragmaOnce(f, lib.name+'_'+LOGMSG_H_FILENAME)
            lib.logmsg.write_define(f)
            configtools.writeFooter(f, mode='C')


def write_system(system):

    # write 'system' file
    with open(join(SYSTEM_DIR, SYSTEM_FILENAME), 'w') as f:
        configtools.writeHeader(f, mode='python')
        f.write(pformat(system.save()))
        configtools.writeFooter(f, mode='python')

    # write 'commands.h' header file in 'system' library
    lib = system.libraries['system']
    with open(join(lib.path, COMMANDS_H_FILENAME), 'w') as f:
        configtools.writeHeader(f, mode='C')
        configtools.writePragmaOnce(f, COMMANDS_H_FILENAME)
        system.commands.write_define(f)
        configtools.writeFooter(f, mode='C')

    # write 'protocol.h' header file in 'system' library
    lib = system.libraries['system']
    pro = system.protocol
    with open(join(lib.path, PROTOCOL_H_FILENAME), 'w') as f:
        configtools.writeHeader(f, mode='C')
        configtools.writePragmaOnce(f, PROTOCOL_H_FILENAME)
        f.write('#include <stdint.h>\n\n')

        types = pro['ptypes']
        configtools.write_typedef(f, 'device', types['device'])
        configtools.write_typedef(f, 'packetSize', types['size'])
        configtools.write_typedef(f, 'command', types['command'])
        configtools.write_typedef(f, 'logmsg', types['logmsg'])
        configtools.write_typedef(f, 'component', types['component'], end='\n\n')

        configtools.write_defineInt(f, 'packet_max_size', pro['packet_max_size'], base=10)
        configtools.write_defineChar(f, 'packet_start', pro['packet_delimiters'][0])
        configtools.write_defineChar(f, 'packet_stop', pro['packet_delimiters'][1])

        configtools.write_defineInt(f, 'uart_baudrate', pro['uart']['baudrate'], base=10)
        configtools.write_defineInt(f, 'uart_timeout', pro['uart']['timeout'], base=10)
        configtools.write_defineInt(f, 'i2c_baudrate', pro['i2c']['baudrate'], base=10)
        configtools.write_defineInt(f, 'i2c_timeout', pro['i2c']['timeout'], base=10, end='\n\n')
        configtools.writeFooter(f, mode='C')


def write_device(system):

    for room in system.rooms.values():
        for dev in room.devices.values(): 

            # write 'logmsg.h' header file in device
            with open(join(dev.path, LOGMSG_H_FILENAME), 'w') as f:
                configtools.writeHeader(f, mode='C')
                configtools.writePragmaOnce(f, LOGMSG_H_FILENAME)
                dev.logmsg.write_define(f)
                configtools.writeFooter(f, mode='C')

            # write 'device.h' header file in device
            hub = room.devices[room.cfg['hub']]
            computer = room.devices[room.cfg['computer']]
            with open(join(dev.path, DEVICE_H_FILENAME), 'w') as f:
                configtools.writeHeader(f, mode='C')
                configtools.writePragmaOnce(f, DEVICE_H_FILENAME)
                dev.write_define(f, name='device')
                room.devices['computer'].write_define(f, name='computer')
                room.devices['router'].write_define(f, name='hub')
                dev.components.write_define(f)
                configtools.writeFooter(f, mode='C')



if __name__ == '__main__':

    system = configtools.System(SYSTEM_DIR)
    write_libslogmsg(system)
    write_system(system)
    write_device(system)

