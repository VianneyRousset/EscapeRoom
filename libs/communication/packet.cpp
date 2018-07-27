#include "packet.hpp"
#include "logger.hpp"
#include "logmsg.h"
#include <string.h>
#include "debug.hpp"
	
// return false in case of failure. In this case, the packet is invalid
template<typename T>
static bool copy(Packet_t* p, T x);
static bool copyStrToPacket(Packet_t* p, va_list args); //TODO

Packet_t createPacket(Device_t src, Device_t dest, Command_t cmd,
		const char* types, va_list args)
{
	Packet_t p;
	p.dest = dest;
	p.src = src;
	p.size = 4;
	p.cmd = cmd;


	while (*types) {
		switch (*types) {
			case '1': if (!copy<uint8_t>(		&p,	va_arg(args, int)))		return p; break;
			case '2': if (!copy<uint16_t>(		&p,	va_arg(args, int)))		return p; break;
			case '4': if (!copy<uint32_t>(		&p,	va_arg(args, int)))		return p; break;
			case '8': if (!copy<uint64_t>(		&p,	va_arg(args, int)))		return p; break;
			case 'b': if (!copy<uint8_t>(		&p,	va_arg(args, int)))		return p; break;
			case 'f': if (!copy<float>(			&p,	va_arg(args, double)))	return p; break;
			case 'd': if (!copy<Device_t>(		&p,	va_arg(args, int)))		return p; break;
			case 'c': if (!copy<Command_t>(		&p,	va_arg(args, int)))		return p; break;
			case 'o': if (!copy<Component_t>(	&p,	va_arg(args, int)))		return p; break;
			case 's': if (!copyStrToPacket(		&p,	va_arg(args, char*)))	return p; break;
			default:
				  loggerp(ERROR_CREATE_PACKET_INVALID_TYPE, "c", *types);
				  p.size = 0; // invalidate packet
				  return p;
		}
		types++;
	}

	return p;
}

template<typename T>
static bool copy(Packet_t* p, T x)
{
	if (p->size + sizeof(x) > PACKET_MAX_SIZE) {
			loggerp(ERROR_CREATE_PACKET_TOO_BIG, "4", PACKET_MAX_SIZE);
			p->size = 0; // invalidate packet
			return false;
	}
		
	memcpy(((uint8_t*) p) + p->size, &x, sizeof(x));
	p->size += sizeof(x);
	return true;
}

static bool copyStrToPacket(Packet_t* p, va_list args)
{
	//TODO
	return false;
}

