#ifndef COMMUNICATION_RECEIVE_PACKET_H_
#define COMMUNICATION_RECEIVE_PACKET_H_

#include "packet.hpp"

// check for a new packet. Return true, if a valid packet is found
bool receivePacket(Packet_t* p);

#endif
