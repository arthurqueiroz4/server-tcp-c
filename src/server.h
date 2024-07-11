//
// Created by arthur on 07/07/24.
//

#include "broadcast.h"

#ifndef SERVER_H
#define SERVER_H

int
setupServerTCP();

int
waitingForAccept(int fd, Broadcast *broadcast);

void
handleConnection(int fd);

void*
handleThreadableConnection(void *args);

#endif //SERVER_H
