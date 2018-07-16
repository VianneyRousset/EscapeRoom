#include "communication.hpp"
#include "debug.hpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

Rooter* rooter;
bool available = true;
Packet_t packet;

void setup()
{                 
	debug_init();
	rooter = new Rooter(COM_ADDRESS_ROOTER);
} 

void loop()
{
	delay(1000);

	if (rooter->fetchInputs() > 0 and available) {
		packet = rooter->pop();
		available = false;
	}

	// handle packet if addressed to rooter
	// if (packet.src == me) {
	// 	blink...
	//	availabe = true;
	// }

	if (!available and rooter->send(&packet) > 0) { // todo == packet.size
		rooter->remove();
		available = true;
	}
}

