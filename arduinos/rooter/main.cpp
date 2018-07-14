#include "communication.hpp"
#include "debug.hpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

Rooter rooter(COM_ADDRESS_ROOTER);
bool available = true;
Packet_t packet;

void setup()
{                 
	debug_init();
} 

void loop()
{
	if (rooter.fetchInputs() > 0 and available) {
		packet = rooter.get();
		available = false;
		debug_blink(3);
	}

	// handle packet if addressed to rooter
	// if (packet.src == me) {
	// 	blink...
	//	availabe = true;
	// }
	
	if (!available and rooter.send(&packet) > 0) // todo == packet.size
		available = true;
}

