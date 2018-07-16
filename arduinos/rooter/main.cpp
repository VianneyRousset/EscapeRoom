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
	if (rooter->fetchInputs() > 0 and available) {
		packet = rooter->pop();
		available = false;
	}

	// handle packet if addressed to rooter
	// if (packet.src == me) {
	// 	blink...
	//	availabe = true;
	// }

	if (!ready and rooter->send(&packet) > 0)
		ready = true;
}

