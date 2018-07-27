#ifndef REQUEST_H_
#define REQUEST_H_

#include <stdint.h>
#include <WString.h>

typedef uint8_t Address_t;

bool request_handler(Address_t src, String msg);

#endif
