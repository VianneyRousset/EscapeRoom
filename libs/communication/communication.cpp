#include "communication.hpp"
#include "logger.hpp"
#include "packet.hpp"
#include "receivePacket.hpp"
#include "sendPacket.hpp"
#include "debug.hpp"

#include <Wire.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

static Device_t HOST = 0, HUB = 0, COMPUTER = 0; 
static bool (*REQUEST_HANDLER)(Device_t src, int n, uint8_t* msg) = nullptr;

// special send only used internally for log purposes
int com_send(uint8_t cmd, const Packet_t* p);

static void onReceiveHandler(int) {}


void com_init(Device_t host, Device_t hub, Device_t computer,
			  bool (*requestHandler)(Device_t src, int n, uint8_t* msg),
			  int uartBaudrate, int uartTimeout,
			  int i2cBaudrate, int i2cTimeout)
{
	HOST= host;
	HUB = hub;
	COMPUTER = computer;
	REQUEST_HANDLER = requestHandler;

	// UART
	Serial.begin(uartBaudrate);
	Serial.setTimeout(uartTimeout);

	// I2C
	Wire.begin(host);
	Wire.setTimeout(i2cTimeout);
	Wire.onReceive(onReceiveHandler);

	//logger(DEBUG_COM_INIT_SUCCESS)
}

int com_send(uint8_t cmd) { return com_send(cmd, ""); }

/*
int com_send(uint8_t cmd, uint8_t p) { return com_send(cmd, "1", p); }
int com_send(uint8_t cmd, uint16_t p) { return com_send(cmd, "2", p); }
int com_send(uint8_t cmd, uint32_t p) { return com_send(cmd, "4", p); }
int com_send(uint8_t cmd, uint64_t p) { return com_send(cmd, "8", p); }
int com_send(uint8_t cmd, float p) { return com_send(cmd, "f", p); }
int com_send(uint8_t cmd, bool p) { return com_send(cmd, "b", p); }
int com_send(uint8_t cmd, const Packet_t* p) { return com_send(cmd, "1p", p); }
*/

int com_send(uint8_t cmd, const char* types,  ...)
{
    va_list args;
    va_start(args, types);
    int n = com_send(cmd, types, args);
    va_end(args);
	return n;
}

int com_send(uint8_t cmd, const char* types, va_list args)
{
	Packet_t p = createPacket(COMPUTER, HOST, cmd, types, args);
	return sendPacket(&p, HOST, HUB, COMPUTER);
}

bool com_gatherRequest(void)
{
	Packet_t p;

	// no new request
	if (receivePacket(&p) <= 0)
		return 0;

	// request execution
	if (p.dest == HOST) {
		if (!REQUEST_HANDLER(p.src, p.cmd, p.args)) {
			//logger(String("Failed to exec: ") + p.str); 
			return -2;
		}
		return 1;
	}

	// routing
	sendPacket(&p, HOST, HUB, COMPUTER);
	//todo:
	//if (address_host != address_router)
	//	log("Received packet with wrong dest");
	return -1;
}


