#include "sendPacket.hpp"

#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

static int sendPacket_uart(const Packet_t* p);
static int sendPacket_i2c(const Packet_t* p, int a);

int sendPacket(const Packet_t* p, Device_t host,Device_t hub,Device_t computer)
{
	// if is router, send to computer with uart or to device via i2c
//	if (host == hub) {
//		if (p->dest == computer)
				return sendPacket_uart(p);
//		return sendPacket_i2c(p, p->dest);
//	}

	// if not router, send to router via i2c
//	return sendPacket_i2c(p, hub);
}

static int sendPacket_uart(const Packet_t* p)
{
	int n = 0;
	n += Serial.write('(');
	n += Serial.write((uint8_t*) p, p->size);
	n += Serial.write(')');
	Serial.flush();
	return n;
}

static int sendPacket_i2c(const Packet_t* p, int i2c_address)
{
	int n = 0;
	Wire.beginTransmission(i2c_address);
	n += Wire.write(PACKET_START);
	n += Wire.write((uint8_t*) p, p->size);
	n += Wire.write(PACKET_STOP);
	Wire.endTransmission();
	return n;
}

