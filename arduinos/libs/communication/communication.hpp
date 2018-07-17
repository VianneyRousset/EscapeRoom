#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdint.h>
#include "config.h"
#include <string.h>
#include <WString.h>
#include <SoftwareSerial.h>

typedef uint8_t Address_t;

namespace Communication {

	// init communication with device addres h and request handler rh
	// (called by execRequest() in case of new packet) 
	void init(Address_t h, bool (*rh)(Address_t src, String msg));

	// Send signed packet with msg. Return nb of sent bytes, 
	int send(const char* msg);
	int send(String msg);

	// Call the request handler once if a least a new packet haven't been read. 
	// If the packet dest isn't this device, the packet is redistributed.
	// In this case, if the device isn't a router, a warning msg is sent.
	// Return:
	//  1 if a request has been treated succefully.
	//  0 if no request was available or that the packet was invalid.
	// -1 if the packet has been routed.
	// -2 in case of request execution failure.
	int execRequest(void);

};

#endif
