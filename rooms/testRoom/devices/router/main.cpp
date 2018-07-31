#include "debug.hpp"
#include "device.h"
#include "communication.hpp"
#include "request.hpp"
#include "logger.hpp"
#include "logmsg.h"
#include <Arduino.h>

//TODO rename router -> hub

void setup()
{                 
	debug_init();
	com_autoinit(request_handler);
	logger(INFO_INIT_SUCCESS);
} 

void loop()
{
	int n = com_send(CMD_STATUS_UPDATE, "ob", COMP_LED_BUILTIN, true);
	delay(1000);
	debug_longblink(n);

	//com_gatherRequest();
}


