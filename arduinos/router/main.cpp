#include "communication.hpp"
#include "debug.hpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

Router* router;
bool ready = true;
Packet_t packet;

static void execRequest(const Packet_t* p);

void setup()
{                 
	debug_init();
	router = new Router(COM_ADDRESS_ROUTER);
} 

void loop()
{
	Packet_t p;
	if (router->receive(&p) > 0) {
		if (p.dest == COM_ADDRESS_ROUTER) {
			execRequest(&p);
		} else {
			router->send(&p);
		}
	}
}

void execRequest(const Packet_t* p)
{
	if (p->str[4] == 's')
		digitalWrite(LED_BUILTIN, p->str[5] == '1' ? HIGH : LOW);
}
