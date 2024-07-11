//
// Created by arthur on 11/07/24.
//

#include "broadcast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Broadcast *newBroadcast() {
    Broadcast *broadcast = malloc(sizeof(Broadcast));

    broadcast->clients = malloc(MAX_CLIENTS * sizeof(Client));
    broadcast->count = 0;

    return broadcast;
}

int addClient(Broadcast *broadcast, struct sockaddr_in client_address) {
    if (broadcast->count >= MAX_CLIENTS)
        return -1;

    int current = broadcast->count;
    broadcast->clients[current].address = client_address;
    broadcast->count++;
    return 0;
}

int removeClient(Broadcast *broadcast, struct sockaddr_in clientAddr) {
    for (int i = 0; i < broadcast->count; i++) {
        if (memcmp(&broadcast->clients[i].address, &clientAddr, sizeof(struct sockaddr))) {
            broadcast->clients[i] = broadcast->clients[broadcast->count - 1];
            broadcast->count--;
            return 0;
        }
    }
    return -1;
}

void broadcastMessage(Broadcast *broadcast, const char *message, int messageLength, int server_fd) {
    for (int i = 0; i < broadcast->count; i++) {
        if (sendto(server_fd, message, messageLength, 0,
                   (struct sockaddr *) &broadcast->clients[i].address, sizeof(struct sockaddr_in)) < 0) {
            perror("sendto failed");
        }
    }
}
