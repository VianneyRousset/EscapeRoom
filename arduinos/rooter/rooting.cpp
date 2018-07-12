#include "rooting.hpp"
#include "communication.hpp"

#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdio.h>
#include <string.h> 

/*

typedef struct {
	Address_t address;
	char msg[65];
} Request_t;

#define REQUESTS_QUEUE_N 128
static Request_t requestsQueue[REQUESTS_QUEUE_N]
static unsigned char requestsQueue_p = 0;
static unsigned char requestsQueue_n = 0;

static char getAddress(char* msg)
{
	address = 0;
	if (sscanf(msg, "%x|", &address) < 0) {
		return -1;
	}
	return address;
}

static unsigned char pushToRequestQueue(Request_t* request)
{
	unsigned char p = (requestsQueue_p + requestsQueue_n) % REQUESTS_QUEUE_N;
	memcpy(&requestsQueue[requestsQueue_p], request);
	return requestsQueue_n++;
}

static Request_t pullFromRequestQueue(Request_t* request)
{
	Request_t request = requestsQueue[requestsQueue_p];
	requestsQueue_p = (requestsQueue_p + 1) % REQUESTS_QUEUE_N;
	requestsQueue_n--;

	return request;
}

void rooting_init(void)
{
	Serial.begin(USB_BAUD_RATE);
	Serial.setTimeout(USB_TIMEOUT);
}

void rooting_pullRequests(void)
{
	char msg[65];
	unsigned char n = 0;

	// USB
	if (Serial.available() > 0) {
		Serial.readBytesUntil('\0', msg, 64);
	}

	if (n > 0) {
		msg[64] = '\0';
		address = getAddress(msg);
		if (address < 0) {
			/// \todo error handling
		}
		
		if (address == ADDRESS_ROOTER
	}
}

*/
