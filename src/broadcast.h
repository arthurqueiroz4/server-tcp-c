//
// Created by arthur on 11/07/24.
//

#ifndef BROADCAST_H
#define BROADCAST_H
#include <netinet/in.h>

typedef struct {
    struct sockaddr_in address;
    int conn_fd;
} Client;

typedef struct {
    Client *clients;
    int count;
} Broadcast;

Broadcast *
newBroadcast();

int
addClient(Broadcast *broadcast, struct sockaddr_in client_address, int conn_fd);

int
removeClient(Broadcast *broadcast, struct sockaddr_in clientAddr);

void
broadcastMessage(Broadcast *broadcast, const char *message, int from_fd);

void
showDetails(Broadcast *broadcast);


#endif // BROADCAST_H
