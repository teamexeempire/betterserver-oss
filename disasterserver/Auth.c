#include <Auth.h>
#include <Server.h>
#include <stdbool.h>
#include <stdint.h>

bool auth_create_ticket(PeerData* peer, Packet* packet)
{
	// Remove useless variables
	PacketWrite(packet, packet_write16, 0);
	PacketWrite(packet, packet_write16, 1);
	PacketWrite(packet, packet_write8, (uint8_t) rand());
	PacketWrite(packet, packet_write8, (uint8_t) rand() % 2);
	PacketWrite(packet, packet_write8, (uint8_t) rand() % 31);
	for (int i = 0; i < 3; i++)
	{
		PacketWrite(packet, packet_write8, 0x00);
	}
	PacketWrite(packet, packet_write32, 1 << 9); 
	return true;
}

bool auth_verify_ticket(PeerData* peer, Packet* packet)
{
	PacketRead(checkcum, packet, packet_read64, uint64_t);
	PacketRead(checkcum2, packet, packet_read64, uint64_t);
	peer->mod_tool = checkcum == 0 || checkcum2 == 0; // set mod tool
	return true;
}
