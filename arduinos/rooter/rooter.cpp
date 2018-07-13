#include "rooter.hpp"
#include "communication.hpp"
#include <SoftwareSerial.h>
#include <Arduino.h>
#include "array.hpp"

#define UART_BAUD_RATE 9600

Rooter::Rooter(Address_t src) : Communication(src)
{
	// UART
	Serial.begin(UART_BAUD_RATE);
	while(!Serial) {;}
	Serial.println("UART initialized");
}

unsigned char Rooter::rootPackets(void)
{
	Packet_t packet;
	unsigned char n = 0;
	while (fetchPackets() > 0) {
		packet = get();
		send(&packet);
		flush();
		n++;
	}

	return n;
}

static unsigned char Rooter::readNewPacketsFromUART(Queue_t* queue)
{
	Packet_t packet;
	unsigned char n = 0;

	while (Serial.available() >= sizeof(packet)) {
		if (Serial.readBytes((char*) &packet, sizeof(packet)) == sizeof(packet)) {
			n++;
		} else {
			;
//			todo: log("Failed to log packet")
		}
	}

	return n;
}

static unsigned char Rooter::readNewPacketsFromI2C(Queue_t* queue)
{
	Packet_t packet;
	unsigned char n = 0;
	// todo
	return n;
}

