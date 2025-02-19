//
// Created by arthur on 11/07/24.
//

#include "broadcast.h"

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <unistd.h>
#define MAX_CLIENTS 100

Broadcast *newBroadcast() {
    Broadcast *broadcast = malloc(sizeof(Broadcast));

    broadcast->clients = malloc(MAX_CLIENTS * sizeof(Client));
    broadcast->count = 0;

    return broadcast;
}

int addClient(Broadcast *broadcast, struct sockaddr_in client_address, int conn_fd) {
    if (broadcast->count >= MAX_CLIENTS)
        return -1;

    int current = broadcast->count;
    broadcast->clients[current].address = client_address;
    broadcast->clients[current].conn_fd = conn_fd;
    broadcast->count++;

    showDetails(broadcast);
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

void broadcastMessage(Broadcast *broadcast, const char *message, int from_fd) {
    printf("Broadcast message started...\n");
    for (int i = 0; i < broadcast->count; i++) {
        Client currentClient = broadcast->clients[i];
        if (currentClient.conn_fd == from_fd) {
            continue;
        }
        ssize_t sent_bytes = send(currentClient.conn_fd, message, strlen(message), 0);
        if (sent_bytes == -1) {
            perror("Failed to send message");
            close(currentClient.conn_fd);
        }
    }
}

void showDetails(Broadcast *broadcast) {
    printf("Clients in broadcast: \n");
    for (int i=0; i<broadcast->count; i++) {
        Client client = broadcast->clients[i];
        printf("%s:%d\n", convertIPToString(client.address.sin_addr), ntohs(client.address.sin_port));
    }
    printf("Total: %d\n\n", broadcast->count);
}
