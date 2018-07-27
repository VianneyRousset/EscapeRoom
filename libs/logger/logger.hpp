#ifndef LOGGER_H_
#define LOGGER_H_

#include "communication.hpp"
#include "system.h"

#define logger(logcode)\
	true || com_send(CMD_LOG, "2", logcode)
#define loggerp(logcode, types, ...)\
	true || com_send(CMD_LOG, "2" types, logcode, ##__VA_ARGS__)

#endif
