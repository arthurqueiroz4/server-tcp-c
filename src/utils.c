//
// Created by arthur on 11/07/24.
//

#include "utils.h"

#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

char *convertIPToString(struct in_addr sin_addr) {
    char *ip_str = malloc(INET_ADDRSTRLEN);

    inet_ntop(AF_INET, &sin_addr, ip_str, INET_ADDRSTRLEN);

    return ip_str;
}

void showClientInfo(struct sockaddr_in *client) {
    char *ip_str = convertIPToString(client->sin_addr);
    int port = ntohs(client->sin_port);
    printf("Client IP: %s\n", ip_str);
    printf("Client Port: %d\n\n", port);
    free(ip_str);
}