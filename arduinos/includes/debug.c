#include "debug.h"
#include <Arduino.h>

void debug_init(void)
{
	pinMode(LED_BUILTIN, OUTPUT);
}

void debug_blink(unsigned short n)
{
	for (unsigned int i = 0; i < n; i++) {
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN, LOW);
		delay(100);
	}
}

