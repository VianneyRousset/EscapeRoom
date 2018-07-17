#include "communication.hpp"
#include "debug.hpp"
#include <Arduino.h>

static bool requestHandler(Address_t src, String msg)
{
	if (msg[0] == 's') {
		digitalWrite(LED_BUILTIN, msg[1] == '1' ? HIGH : LOW);
		Communication::send(String("Setting light ") + String(msg[1] == '1' ? "ON" : "OFF"));
	}
	return true;
}

void setup()
{                 
	debug_init();
	Communication::init(COM_ADDRESS_CLOCK, requestHandler);
} 

void loop()
{
	Communication::execRequest();
}

