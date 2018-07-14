#include "communication.hpp"
#include "array.hpp"
#include <SoftwareSerial.h>
#include "debug.hpp"
#include <Arduino.h>

Packet_t inputBuffer[COM_INPUT_QUEUE_N], outputBuffer[COM_OUTPUT_QUEUE_N];
Queue_t inputQueue, outputQueue;

#define INPUTS_SIZE 512
#define READ_TIMEOUT 1000

Communication::Communication(Address_t addr) : inputs(INPUTS_SIZE), address(addr)
{} 

Packet_t Communication::get(void)
{
	const char* str = inputs.get();
	Packet_t packet = {COM_ADDRESS_COMPUTER, COM_ADDRESS_COMPUTER, nullptr}; //default, COM_ADDR_NULL? 
	if (str)
		sscanf(str,"%2" SCNu8 "%2" SCNu8, &packet.dest, &packet.src);
	return packet; 
}

Rooter::Rooter(Address_t addr) : Communication(addr)
{
	// UART
	Serial.begin(UART_BAUD_RATE);
	while(!Serial) {;}
	Serial.setTimeout(READ_TIMEOUT);
}

unsigned short Rooter::fetchInputs(void)
{
	while (Serial.available() > 0) {
		char* str = Serial.readStringUntil('\0').c_str();
		inputs.push(str);
	}
	return inputQueue.n;
}

size_t Rooter::send(const Packet_t* packet)
{
	switch(packet->dest) {
	case COM_ADDRESS_COMPUTER:
		if (Serial.availableForWrite())
			return Serial.write(packet->str);
		return 0;
	default:
		return 1; //todo, i2c...
	}
}

