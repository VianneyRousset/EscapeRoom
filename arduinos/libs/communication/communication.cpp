#include "communication.hpp"
#include <SoftwareSerial.h>
#include "debug.hpp"
#include <Arduino.h>

#define INPUTS_SIZE 512
#define READ_TIMEOUT 10000

Communication::Communication(Address_t addr) : address(addr)
{} 

Rooter::Rooter(Address_t addr) : Communication(addr)
{
	Serial.begin(UART_BAUD_RATE);
	Serial.setTimeout(READ_TIMEOUT);

	Serial.println("UART initialized");
}

int Rooter::receive(Packet_t* p)
{
	int a = Serial.available();
	if (a > 0) {
		p->str = Serial.readStringUntil(PACKET_TERMINATOR);
		sscanf(p->str.c_str(),"%2" SCNu8 "%2" SCNu8, &p->dest, &p->src);
	}
	return a;
}

size_t Rooter::send(const Packet_t* packet)
{
	switch(packet->dest) {
		case COM_ADDRESS_COMPUTER:
			return Serial.println(packet->str);
		default:
			return 1; //todo, i2c...
	}
}

