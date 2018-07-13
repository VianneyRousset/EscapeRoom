#include "communication.hpp"
#include "private.hpp"
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

unsigned char Communication::fetchPackets(void)
{
	//unsigned char nUART = readNewPacketsFromUART(&inputQueue);
	//unsigned char nI2C = readNewPacketsFromI2C(&inputQueue);

	//if (nUART < 0 || nI2c < 0)
		// todo: log("inputQueue full")

	return inputQueue.n;
}

unsigned char Communication::available(void)
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

unsigned char Communication::send(const Packet_t* packet)
{
	queue_push(&outputQueue, packet);
		// if < 0
		// todo: log("full output queue")
	return outputQueue.n;
}

void Communication::flush(void)
{
	Serial.println("hello folk");
	// todo: flush for non-rooter devices
	if (Serial.available()) {
		Serial.write(Serial.read());
	}
}

