#include "rooting.hpp"
#include "communication.hpp"

void rooting_init(void)
{
	com_init();
}

unsigned char rooting_rootPackets(void)
{
	Packet_t packet;
	unsigned char n = 0;
	while (com_fetchPackets() > 0) {
		packet = com_get();
		com_send(&packet);
		com_flush();
		n++;
	}

	return n;
}
