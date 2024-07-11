//
// Created by arthur on 07/07/24.
//
#ifndef SERVER_H
#define SERVER_H

#include "broadcast.h"

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

int
setupServerTCP();

int
waitingForAccept(int fd, Broadcast *broadcast);

void
handleConnection(int conn_fd, Broadcast *broadcast);

void*
handleThreadableConnection(void *args);

#endif //SERVER_H