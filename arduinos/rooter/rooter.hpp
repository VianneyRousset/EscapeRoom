#ifndef ROOTING_H_
#define ROOTING_H_

#include "communication.hpp"
#include "array.hpp"

class Rooter : public Communication {
private:
	static unsigned char readNewPacketsFromUART(Queue_t* queue);
	static unsigned char readNewPacketsFromI2C(Queue_t* queue);

public:
	Rooter(Address_t src);

	void flush(void); // return amount of flushed packets?

	unsigned char rootPackets(void);
};

#endif
