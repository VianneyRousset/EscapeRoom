#include "rooter.hpp"
#include "communication.hpp"
#include "debug.hpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

Rooter rooter(COM_ADDRESS_ROOTER);

void setup()
{                 
	debug_init();
//	com_init();
} 

void loop()
{  
//	com_flush();
}

