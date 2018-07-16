#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdint.h>
#include "config.h"
#include <string.h>
#include <Arduino.h>
#include <WString.h>

typedef uint8_t Address_t;

typedef struct {
	Address_t dest, src;
	String str;
} Packet_t;

class Communication {
	public:
		Address_t address;

		Communication(Address_t src);
		virtual int receive(Packet_t* packet);
		virtual size_t send(const Packet_t* packet) = 0;
};

class Router : public Communication {
	public:
		Router(Address_t src);
		int receive(Packet_t* packet);
		size_t send(const Packet_t* packet);
};

#endif
