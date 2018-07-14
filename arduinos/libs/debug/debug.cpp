#include "debug.hpp"
#include <Arduino.h>

void debug_init(void)
{
	pinMode(LED_BUILTIN, OUTPUT);
}

void debug_shortblink(unsigned short n)
{
	for (unsigned short i = 0; i < n; i++) {
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
	}
}

void debug_longblink(unsigned short n)
{
	for (unsigned short i = 0; i < n; i++) {
		digitalWrite(LED_BUILTIN, HIGH);
		delay(200);
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
	}
}
