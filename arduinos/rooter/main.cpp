#include "rooting.hpp"
#include "debug.h"

void setup(void)
{
	debug_init();
	rooting_init();
}

void loop(void)
{
	unsigned char n = 0;
	n = rooting_rootPackets();
	debug_blink(n);
}
