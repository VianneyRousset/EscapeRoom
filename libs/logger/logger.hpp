#ifndef LOGGER_H_
#define LOGGER_H_

#include "communication.hpp"
#include "system.h"

#define logger(logcode, ...) com_send(CMD_LOG, ##__VA_ARGS__)

#endif
