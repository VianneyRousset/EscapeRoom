#include "debug.hpp"
#include "address.hpp"
#include "device.hpp"
#include "communication.hpp"
#include <Arduino.h>
#include "request.hpp"
#include "logger.hpp"

void setup()
{                 
	debug_init();
	com_autoinit(request_handler)

	logger_info("Init success"); //TODO: not really true
} 

void loop()
{
	com_gatherRequest();
}


