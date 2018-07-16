#include "communication.hpp"
#include <SoftwareSerial.h>
#include "debug.hpp"
#include <Arduino.h>

#define INPUTS_SIZE 512
#define READ_TIMEOUT 1000

Communication::Communication(Address_t addr) : address(addr)
{} 

int Rooter::receive(Packet_t* packet)
{
	int a = Serial.available();
	if (a > 0) {
		packet->str = Serial.readStringUntil('\n');
		sscanf(packet->str.c_str(),"%2" SCNu8 "%2" SCNu8, &packet->dest, &packet->src);
	}
	return a;
}

Rooter::Rooter(Address_t addr) : Communication(addr)
{
	Serial.begin(UART_BAUD_RATE);
	while(!Serial) {;}
	Serial.setTimeout(READ_TIMEOUT);

	Serial.println("UART initialized");
}

size_t Rooter::send(const Packet_t* packet)
{
	if (Serial.availableForWrite() >= sizeof(packet->str))
		return Serial.println(packet->str);
	return 0;
	/*
	switch(packet->dest) {
	case COM_ADDRESS_COMPUTER:
		if (Serial.availableForWrite()) {
			debug_longblink(2);
			//return Serial.println(packet->str);
			return Serial.println("salut");
		}
		return 0;
	default:
		return 1; //todo, i2c...
	}
	*/
}

