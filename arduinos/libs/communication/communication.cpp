#include "communication.hpp"
#include "config.h"
#include "debug.hpp"
#include <SoftwareSerial.h>
#include <Arduino.h>
#include <Wire.h>

static Address_t host = 0;
static bool (*requestHandler)(Address_t src, String msg) = nullptr;

typedef struct {
	Address_t dest, src;
	String str;
} Packet_t;

// check for a new packet. Return number of bytes read. 
static int receive(Packet_t* p);

// send packet. Return nb of sent bytes
static int sendPacket(const Packet_t* p);

// create Packet with destination dest, source src and message msg
static Packet_t createPacket(Address_t dest, Address_t src, String msg);

// fill packet p with dest, src and str comming from package string pstr
// return 0 if the packet is invalid, 1 if the packet is valid
static bool parsePstr(String pstr, Packet_t* p);

// fill dest and src with packet string pstr info. Return 0 in case of
// failure and 1 in case of success.
static bool getPacketHeader(String pstr, Address_t* dest, Address_t* src);

// return msg string from packet string pstr
static String getPacketMsg(String pstr) { return pstr.substring(4); }

// doing nothing : needed for Wire library 
static void onReceiveHandler(int) {}

void Communication::init(Address_t h, bool (*rh)(Address_t src, String msg))
{
	host = h;
	requestHandler = rh;

	// UART
	Serial.begin(UART_BAUD_RATE);
	Serial.setTimeout(UART_TIMEOUT);

	// I2C
	Wire.begin(I2C_ADDRESSES[host]);
	Wire.setTimeout(I2C_TIMEOUT);
	Wire.onReceive(onReceiveHandler);

	send("Communication initialized"); // todo: use log
}

int Communication::send(const char* msg)
{
	return send(String(msg));
}

int Communication::send(String msg)
{
	Packet_t p = createPacket(COM_ADDRESS_COMPUTER, host, msg);
	return sendPacket(&p);
}

int Communication::execRequest(void)
{
	Packet_t p;

	// no new request
	if (receive(&p) <= 0)
		return 0;

	// request execution
	if (p.dest == host)
			return requestHandler(p.src, getPacketMsg(p.str)) ? 1 : -2;

	// routing
	sendPacket(&p);
	//todo:
	//if (host != COM_ADDRESS_ROUTER)
	//	log_warn("Received packet with wrong dest");
	return -1;
}

static int receive(Packet_t* p)
{
	int a = 0;
	
	// UART
	a = Serial.available();
	if (a > 0) {
		p->str = Serial.readStringUntil(PACKET_TERMINATOR);
		if(!parsePstr(p->str, p)) {
			// todo: log_error(String("Received invalid package : ") + p->pstr);
			return 0;
		}
		return a;
	}

	// I2C
	a = Wire.available();
	if (a > 0) {
		p->str = Wire.readStringUntil(PACKET_TERMINATOR);
		if(!parsePstr(p->str, p)) {
			// todo: log_error(String("Received invalid package : ") + p->pstr);
			return 0;
		}
		return a;

	}

	return 0;
}

static int sendPacket(const Packet_t* p)
{
	Address_t I2Caddr = I2C_ADDRESSES[COM_ADDRESS_ROUTER];

	if (host == COM_ADDRESS_ROUTER) {
		if (p->dest == COM_ADDRESS_COMPUTER)
			return Serial.println(p->str);
		I2Caddr = I2C_ADDRESSES[p->dest];
	}

	Wire.beginTransmission(I2Caddr);
	int n = Wire.println(p->str);
	Wire.endTransmission();
	return n;
}

static Packet_t createPacket(Address_t dest, Address_t src, String msg)
{
	Packet_t p;
	char headerStr[] = "    ";
	sprintf(headerStr, "%02x%02x", dest, src);
	p.src = host;
	p.dest = COM_ADDRESS_COMPUTER;
	p.str= String(headerStr) + msg;
	return p;
}

static bool getPacketHeader(String pstr, Address_t* dest, Address_t* src)
{
	return sscanf(pstr.c_str(),"%2" SCNu8 "%2" SCNu8, dest, src) >= 2;
}

static bool parsePstr(String pstr, Packet_t* p)
{
	p->str = pstr;
	if (!getPacketHeader(pstr, &p->dest, &p->src))
		return 0;
	return 1;
}
