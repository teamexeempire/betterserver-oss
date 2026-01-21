#include <Auth.h>
#include <Server.h>
#include <stdbool.h>
#include <stdint.h>

const uint32_t authTypeOne = 1 << 9;
const uint32_t authTypeTwo = 1 << 31;
const uint32_t authTypeThree = 1 << 26;
const uint32_t authTypesAll = authTypeOne | authTypeTwo | authTypeThree;
const uint32_t authTypes[] = { authTypeOne, authTypeTwo, authTypeThree };

bool auth_create_ticket(PeerData* peer, Packet* packet)
{
	peer->auth.one = (uint8_t) rand();
	peer->auth.two = (uint8_t) rand() % 31;
	peer->auth.type = rand() & ~authTypesAll;
	// Red herrings? Nah, we have Red Rope(TM)
	// All values here are complete bogus btw
	PacketWrite(packet, packet_write16, 0);
	PacketWrite(packet, packet_write16, 1);
	PacketWrite(packet, packet_write8, peer->auth.one);
	PacketWrite(packet, packet_write8, (uint8_t) rand() % 2);
	PacketWrite(packet, packet_write8, peer->auth.two);
	const char balls[] = { 0xff, 0x1c, 0x22, 0x00, 0x14, 0x80 };
	for (int i = 0; i < 3; i++)
	{
		PacketWrite(packet, packet_write8, balls[rand() % sizeof(balls)]);
	}
	PacketWrite(packet, packet_write32, peer->auth.type);
	return true;
}

bool auth_verify_ticket(PeerData* peer, Packet* packet)
{
	PacketRead(checkcum, packet, packet_read64, uint64_t);
	PacketRead(checkcum2, packet, packet_read64, uint64_t);
	peer->mod_tool = checkcum == 0 || checkcum2 == 0;
	return true;
}
