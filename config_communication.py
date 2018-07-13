#!/usr/bin/env python
#
#						       +---------+
#					          ---> |  clock  |
#	+----------+   UART  +--------+	   I2C   /     +---------+
#	| computer | <-----> | rooter | <------------> | puzzle1 |
#	+----------+         +--------+	         \     +---------+
#						  ---> | puzzle2 |
#						       +---------+
#
#   A packet is composed as follows:
#				
#	packet = header + fragment 
#
#       header = destination + source + fragment_n + fragement_i
#
#           ->  destination is the destination host address. (8b)
#           ->  source is the source host address. (8b)
#           ->  dataFragment_n is the total number of data fragments to wait.
#               for. (8b)
#           ->  dataFragment_i is the id of data fragments in this packet. It
#               has to be between 0 and dataFragment_n-1. (8b)
#
#   *header*
#   The header store all the metadata of the packet.
#
#   *fragment*
#   The data is cut in fragments of COMMUNICATION_FRAGMENT_SIZE bytes each.
#   Each fragement commes with a id dataFragment_i and the data total number
#   of fragments dataFragment_n in the header.
#
#   *Address*
#   Address is included in [0x00, 0xff] therefore a char. The type Address_t
#   or the enum Address_e defined as a int8 is are good variable type to
#   store it.
#

cPublicHeaderFile = 'arduinos/includes/communication.hpp'
cPrivateHeaderFile = 'arduinos/includes/private/communication.hpp'

# packet
headerSize = 2; # in bytes
dataSize = 14; # in bytes
inputQueueSize = 64 # in nb of packets
outputQueueSize = 64 # in nb of packets

# commands
commands = [  #  NAME               CODE    DESCRIPTION
                ('nope',            0x00,   'Do nothing.'),
                ('ping',            0x01,   'Ask for akw.'),
                ('aknowledge',      0x02,   'Aknowledge data.'),
                ('status',          0x03,   'Status data.'),
                ('log',             0x04,   'Log data.'),
                ('reset',           0x05,   'Complete reset.')]

# addresses
addresses = [ #  NAME               ADDRESS         I2C_ADDRESS
                ('rooter',          0x00,           0x00),
                ('computer',        0x01,           None),
                ('clock',           0x02,           0x02),
                ('puzzle1',         0x03,           0x03),
                ('puzzle2',         0x04,           0x04)]

# UART 
uartTimeout = 1000 # in ms
uartBaudRate = 9600

# I2C
i2cBaudRate = 9600

# post treatement
for i,a in enumerate(addresses):
    addresses[i] = {'name':a[0], 'address':a[1], 'i2c_address':a[2]}
