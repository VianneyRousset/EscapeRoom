#include "communication.hpp"
#include "array.hpp"
#include <SoftwareSerial.h>
#include "debug.hpp"
#include <Arduino.h>

#define INPUTS_SIZE 512
#define READ_TIMEOUT 1000

Communication::Communication(Address_t addr) : inputs(INPUTS_SIZE), address(addr)
{} 

Packet_t Communication::pop(void)
{
	const char* str = inputs.get();
	Packet_t packet = {COM_ADDRESS_COMPUTER, COM_ADDRESS_COMPUTER, nullptr}; //default? 
	if (str) {
		sscanf(str,"%2" SCNu8 "%2" SCNu8, &packet.dest, &packet.src);
		packet.str = str;
	}
	return packet; 
}

void Communication::remove()
{
	inputs.remove();
}

Rooter::Rooter(Address_t addr) : Communication(addr)
{
	Serial.begin(UART_BAUD_RATE);
	while(!Serial) {;}
	Serial.setTimeout(READ_TIMEOUT);

	Serial.println("UART initialized");
}

unsigned short Rooter::fetchInputs(void)
{
	while (Serial.available() > 0) {
		String str = Serial.readString();
		inputs.push(str.c_str());
	}
	return inputs.n;
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

