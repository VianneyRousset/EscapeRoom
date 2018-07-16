#include "communication.hpp"
#include "debug.hpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

Rooter* rooter;
bool ready = true;
Packet_t packet;

void setup()
{                 
	debug_init();
	rooter = new Rooter(COM_ADDRESS_ROOTER);
} 

void loop()
{
	Packet_t p;
	if (rooter->receive(&p) > 0)
		rooter->send(&p);
}

