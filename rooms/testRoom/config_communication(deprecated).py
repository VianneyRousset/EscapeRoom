#!/usr/bin/env python
#
#						       +---------+
#					          ---> |  clock  |
#	+----------+   UART  +--------+	   I2C   /     +---------+
#	| computer | <-----> | router | <------------> | puzzle1 |
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
