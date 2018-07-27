// This file has been autogenerated by configure.py please modify config_*.py
// files and run configure.py instead of modifying this file.

#ifndef DEVICE_H_
#define DEVICE_H_

#include <stdint.h>
                
#define DEV_NAME "puzzle1"
#define DEV_ADDRESS 0x03

typedef uint8_t Command_t;

typedef enum : Command_t {
	CMD_PING = 0x00,
	CMD_GET = 0x01,
	CMD_SET = 0x02
} Command_e;


typedef uint8_t ReturnCode_t;

typedef enum : ReturnCode_t {
	RTN_LOG_ERROR = 0x80,
	RTN_LOG_WARN = 0x81,
	RTN_LOG_INFO = 0x82,
	RTN_PING_BACK = 0x90,
	RTN_STATUS_UPDATE = 0x91
} ReturnCode_e;


typedef uint8_t Component_t;

typedef enum : Component_t {
	COMP_LED_BUILTIN = 0x00
} Component_e;

#endif
