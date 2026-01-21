#ifndef AUTH_H
#define AUTH_H
#include <Packet.h>
#include <Player.h>

// remove useless stuff

typedef struct PeerData PeerData;

bool auth_create_ticket(PeerData* peer, Packet* packet);
bool auth_verify_ticket(PeerData* peer, Packet* packet);

#endif
