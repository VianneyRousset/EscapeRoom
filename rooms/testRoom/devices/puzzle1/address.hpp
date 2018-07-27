// This file has been autogenerated by configure.py please modify config_*.py
// files and run configure.py instead of modifying this file.

#ifndef ADDRESS_H_ 
#define ADDRESS_H_
                
#include <stdint.h>
                
typedef uint8_t Address_t;

typedef enum : Address_t {
	COM_ADDRESS_COMPUTER = 0x01,
	COM_ADDRESS_ROUTER = 0x00,
	COM_ADDRESS_CLOCK = 0x02,
	COM_ADDRESS_PUZZLE1 = 0x03,
	COM_ADDRESS_PUZZLE2 = 0x04
} Address_e;


#define PACKET_TERMINATOR '\n'

#define UART_BAUDRATE 9600
#define UART_TIMEOUT 1000

typedef uint8_t I2C_address_t;
#define I2C_BAUDRATE 9600
#define I2C_TIMEOUT 1000


I2C_address_t I2C_TABLE[128] = {
	0x01,    0, 0x02, 0x03, 0x04,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0
};

#endif
