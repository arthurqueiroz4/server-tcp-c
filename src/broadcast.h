//
// Created by arthur on 11/07/24.
//

#ifndef BROADCAST_H
#define BROADCAST_H

#include <netinet/in.h>

#define MAX_CLIENTS 100

struct Client {
    struct sockaddr_in address;
} typedef Client;

struct Broadcast {
    Client *clients;
    int count;
} typedef Broadcast;

Broadcast *
newBroadcast();

int
addClient(Broadcast *broadcast, struct sockaddr_in client_address);

int
removeClient(Broadcast *broadcast, struct sockaddr_in clientAddr);

void
broadcastMessage(Broadcast *broadcast, int sender_fd, const char *message);

#endif // BROADCAST_H
