#include "communication.hpp"
#include "private/communication.hpp"
#include "array.h"
#include <Serial.h>

Packet_t inputBuffer[COM_INPUT_QUEUE_N], outputBuffer[COM_OUTPUT_QUEUE_N];
Queue_t inputQueue, outputQueue;

static unsigned char readNewPacketsFromUART(Queue_t* queue)
{
	Packet_t packet;
	unsigned char n = 0;
	
	while (Serial.available() >= sizeof(packet)) {
		if (Serial.readBytes(&packet, sizeof(packet)) == sizeof(packet)) {
			n++
//		} else {
//			todo: log("Failed to log packet")
		}
	}

	return n;
}

static unsigned char readNewPacketsFromI2C(Queue_t* queue)
{
	Packet_t packet;
	unsigned char n = 0;
	// todo
	return n;
}

void com_init(void)
{
	// queues
	inputQueue = queue_create(	&inputBuffer,
								COM_INPUT_QUEUE_N,
								sizeof(packet));
	outputQueue = queue_create(	&outputBuffer,
								COM_OUTPUT_QUEUE_N,
								sizeof(packet));

	// UART
	Serial.begin(UART_BAUD_RATE);
}

unsigned char com_fetchPackets(void)
{
	unsigned char nUART += readNewPacketsFromUART(&inputBuffer)
	unsigned char nI2C += readNewPacketsFromI2C(&inputBuffer)

	//if (nUART < 0 || nI2c < 0)
		// todo: log("inputQueue full")

	return inputQueue.n;
}

unsigned char com_available(void)
{
	return inputQueue.n;
}

Packet_t com_get(void)
{
	Packet_t packet;
	queue_pull(&inputQueue, &packet);
		// if < 0
		// todo: log("empty input queue")
	return packet

}

unsigned char com_send(const Packet_t* packet)
{
	queue_push(&outputQueue, packet);
		// if < 0
		// todo: log("full output queue")
	return outputQueue.n;
}

#if True // todo: replace by #if DEVICE == "rooter"
void com_flush(void)
{
	Packet_t packet;
	while (queue_pull(outputQueue, &packet) > 0) {
		Serial.write(&packet, sizeof(packet));
		Serial.flush();
	}
}
#else
void com_flush(void)
{
	// todo: flush for non-rooter devices
}
#endif

