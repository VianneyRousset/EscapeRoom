//#include "rooting.hpp"
#include "communication.hpp"

#include <Arduino.h>

void setup(void)
{
//	rooting_init();
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop(void)
{
	digitalWrite(LED_BUILTIN, HIGH);
	delay(100);
	digitalWrite(LED_BUILTIN, LOW);
	delay(100);
	Serial.println("Hello Computer");
	Serial.flush();
}
