#ifndef COMMUNICATION_SEND_PACKET_H_
#define COMMUNICATION_SEND_PACKET_H_

#include "packet.hpp"
#include "system.h"
#include <stdarg.h>

// send packet. Return nb of sent bytes
int sendPacket(const Packet_t* p, Device_t host,Device_t hub,Device_t computer);

#endif
