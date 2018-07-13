#include "rooting.hpp"
#include "communication.hpp"
#include "debug.hpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

void setup()
{                
	debug_init();
	com_init();
}

void loop()
{
	com_flush();
	debug_blink(3);
	delay(2000);
}

