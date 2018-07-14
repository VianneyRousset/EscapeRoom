#include "communication.hpp"
#include "array.hpp"
#include <SoftwareSerial.h>
#include "debug.hpp"
#include <Arduino.h>

Packet_t inputBuffer[COM_INPUT_QUEUE_N], outputBuffer[COM_OUTPUT_QUEUE_N];
Queue_t inputQueue, outputQueue;

Communication::Communication(Address_t s)
{
	src = s;
	/*
	// queues
	inputQueue = queue_create(	&inputBuffer,
								COM_INPUT_QUEUE_N,
								sizeof(Packet_t));
	outputQueue = queue_create(	&outputBuffer,
								COM_OUTPUT_QUEUE_N,
								sizeof(Packet_t));
	*/
}

unsigned char Communication::pendingInputs(void)
{
	return inputQueue.n;
}

Packet_t Communication::get(void)
{
	Packet_t packet;
	queue_pull(&inputQueue, &packet);
		// if < 0
		// todo: log("empty input queue")
	return packet;

}


Rooter::Rooter(Address_t src) : Communication(src)
{
	// UART
	Serial.begin(UART_BAUD_RATE);
	while(!Serial) {;}
	Serial.println("UART initialized");

	// todo i2c
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

unsigned char Rooter::fetchPackets(void)
{
	unsigned char nUART = readNewPacketsFromUART(&inputQueue);
	//unsigned char nI2C = readNewPacketsFromI2C(&inputQueue);

	//if (nUART < 0 || nI2c < 0)
		// todo: log("inputQueue full")

	return inputQueue.n;
}

size_t Rooter::send(const Packet_t* packet)
{
	switch(packet->dest) {
	case COM_ADDRESS_COMPUTER:
		if (Serial.availableForWrite())
			return Serial.write("todo");
		return 0;
	default:
		return 1; //todo, i2c...
	}
}


Module::Module(Address_t src) : Communication(src)
{
	// todo i2c
}

static unsigned char Module::readNewPacketsFromI2C(Queue_t* queue)
{
	Packet_t packet;
	unsigned char n = 0;
	// todo
	return n;
}

unsigned char Module::fetchPackets(void)
{
	unsigned char n = readNewPacketsFromI2C(&inputQueue);

	//if (nUART < 0 || nI2c < 0)
		// todo: log("inputQueue full")

	return n;
}

size_t Module::send(const Packet_t* packet)
{
	switch(packet->dest) {
	default:
		return 1; //todo, i2c...
	}
}

