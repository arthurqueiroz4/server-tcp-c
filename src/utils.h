//
// Created by arthur on 11/07/24.
//


#ifndef UTILS_H
#define UTILS_H

#include <netinet/in.h>
#include "broadcast.h"

typedef struct {
    int connfd;
    Broadcast *broadcast;
} ParamsForThread;

char *
convertIPToString(struct in_addr sin_addr);

void
showClientInfo(struct sockaddr_in *client);

#endif //UTILS_H
