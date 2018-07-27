#include "debug.hpp"
#include "device.h"
#include "communication.hpp"
#include "request.hpp"
#include "logger.hpp"
#include <Arduino.h>

//TODO rename router -> hub

void setup()
{                 
	debug_init();
	com_autoinit(request_handler);
	//Serial.begin(9600);

//	logger_info(); //TODO: not really true
} 

void loop()
{
	int n = com_send(CMD_PING_BACK);
	delay(1000);
	debug_longblink(n);

	//com_gatherRequest();
}


