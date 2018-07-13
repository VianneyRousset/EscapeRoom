#include "rooting.hpp"
#include "debug.h"

void setup()
{
	debug_init();
	rooting_init();
}

void loop()
{
	unsigned char n = 0;
	n = rooting_rootPackets();
	debug_blink(n);
}

int main(void)
{
	setup();
	while (1) {
		loop();
	}
	return 0;
}
