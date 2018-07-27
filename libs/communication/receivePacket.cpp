#include "receivePacket.hpp"
#include "logger.hpp"
#include "logmsg.h"

#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

#define BUFFER_SIZE 64

template<class T>
static int readPacket(Packet_t* p, T io);

bool receivePacket(Packet_t* p)
{
	return readPacket<TwoWire>(p, Wire) || readPacket<HardwareSerial>(p, Serial);
}

//TODO if garbage contain START, it may miss a packet by reading part of it
template<class T>
static int readPacket(Packet_t* p, T io)
{
	int n = 0, m = 0;
	uint8_t buffer[BUFFER_SIZE];

#define read(dest, msg) \
	if (io.readBytes((uint8_t*) &dest, sizeof(dest)) != sizeof(dest)) { \
		logger(msg); \
		continue; \
	}

	while ( (n = min(io.available(), BUFFER_SIZE)) > 0) {

		// read until START or avalaible bytes
		m = io.readBytesUntil(PACKET_START, buffer, n);

		// check if no START has been found
		if (n == m && buffer[n-1] != PACKET_START) continue;

		// read packet size
		read(p->size, ERROR_READ_FAIL_PACKET_SIZE)

		// packet size too big
		if (p->size > PACKET_MAX_SIZE) {
			loggerp(ERROR_READ_PACKET_SIZE_TOO_BIG, "22", p->size,
														PACKET_MAX_SIZE);
			continue;
		}

		// packet size too small
		if (p->size < PACKET_HEADER_SIZE) {
			loggerp(ERROR_READ_PACKET_SIZE_TOO_SMALL, "22", p->size,
														PACKET_HEADER_SIZE);
			continue;
		}

		// packet size cannot contain cmd
		if (p->size == PACKET_HEADER_SIZE) {
			loggerp(ERROR_READ_PACKET_MISSING_CMD, "22", p->size,
														PACKET_HEADER_SIZE);
			continue;
		}

		// read packet src, dest, cmd and remaining
		read(p->src, ERROR_READ_FAIL_PACKET_SRC)
		read(p->dest, ERROR_READ_FAIL_PACKET_DEST)
		read(p->cmd, ERROR_READ_FAIL_PACKET_CMD)
		if (io.readBytes((uint8_t*) &p->args, p->size) != p->size) {
			logger(ERROR_READ_FAIL_PACKET_ARGS);
			continue;
		}

		return true;
	}

	return false;
#undef read
}
