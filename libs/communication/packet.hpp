#ifndef COMMUNICATION_PACKET_T
#define COMMUNICATION_PACKET_T

#include "system.h"
#include <stdarg.h>

#define PACKET_HEADER_SIZE sizeof(Packetsize_t)+2*sizeof(Device_t)

typedef struct {
	Packetsize_t size;
	Device_t src, dest;
	Command_t cmd;
	uint8_t args[PACKET_MAX_SIZE-PACKET_HEADER_SIZE-sizeof(Command_t)];
} Packet_t;

// create Packet with destination dest, source src and message msg
// types are:	'1' (uint8_t), '2' (uint16_t), '4' (uint32_t), '8' (uint64_t),
//				'f' (float32), 'p' (Packet_t), 'b' (uint8_t), 's' (string) 
Packet_t createPacket(Device_t src, Device_t dest, Command_t cmd,
		const char* types, va_list args);

#endif
