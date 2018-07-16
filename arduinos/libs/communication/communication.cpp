#include "communication.hpp"
#include "debug.hpp"
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Wire.h>

#define INPUTS_SIZE 512
#define READ_TIMEOUT 10000

Communication::Communication(Address_t addr) : address(addr)
{} 

Router::Router(Address_t addr) : Communication(addr)
{
	// UART
	Serial.begin(UART_BAUD_RATE);
	Serial.setTimeout(READ_TIMEOUT);
	Serial.println("UART initialized");

	// I2C
	Wire.begin(I2C_ADDRESSES[this->address]);
	Serial.println("I2C initialized");
}

int Router::receive(Packet_t* p)
{
	int a = 0;
	
	// UART
	a = Serial.available();
	if (a > 0) {
		p->str = Serial.readStringUntil(PACKET_TERMINATOR);
		sscanf(p->str.c_str(),"%2" SCNu8 "%2" SCNu8, &p->dest, &p->src);
		return a;
	}

	// I2C
	a = Wire.available();
	if (a > 0) {
		p->str = Wire.readStringUntil(PACKET_TERMINATOR);
		sscanf(p->str.c_str(),"%2" SCNu8 "%2" SCNu8, &p->dest, &p->src);
		return a;
	}
}

size_t Router::send(const Packet_t* packet)
{
	switch(packet->dest) {
		case COM_ADDRESS_COMPUTER:
			return Serial.println(packet->str);
		default:
			return Wire.println(packet->str);
	}
}

