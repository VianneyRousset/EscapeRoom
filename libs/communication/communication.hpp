#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include "system.h"
#include <stdarg.h>

#define com_autoinit(requestHandler) \
	com_init(DEVICE, HUB, COMPUTER, requestHandler, \
			 UART_BAUDRATE, UART_TIMEOUT, \
			 I2C_BAUDRATE, I2C_TIMEOUT)

// requestHandler is called by com_gatherRequest() in case of new packet 
void com_init(Device_t host, Device_t hub, Device_t computer,
			  bool (*requestHandler)(Device_t src, int n, uint8_t* msg),
			  int uartBaudrate, int uartTimeout,
			  int i2cBaudrate, int i2cTimeout);

// Return nb of sent bytes or -1 in case of failure 
// types are:	'1' (uint8_t), '2' (uint16_t), '4' (uint32_t), '8' (uint64_t),
//				'f' (float32), 'p' (Packet_t), 'b' (uint8_t), 's' (string) 
int com_send(uint8_t cmd);
int com_send(uint8_t cmd, const char* types, ...);
int com_send(uint8_t cmd, const char* types, va_list args);



// Call the request handler once if a least a new packet haven't been read. 
// If the packet dest isn't this device, the packet is redistributed.
// In this case, if the device isn't a router, a warning msg is sent.
// Return:
//  1 if a request has been treated succefully otherwise.
bool com_gatherRequest(void);

#endif
