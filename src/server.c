//
// Created by arthur on 07/07/24.
//
#include "server.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "utils.h"
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

int createSocketTCP() {
    int const sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Socket creation failed...\n");
        exit(1);
    }
    printf("Socket created...\n");

    return sockfd;
}

void configServAddr(struct sockaddr_in* servAddr) {
    memset(servAddr, 0, sizeof(servAddr));

    servAddr->sin_family = AF_INET;
    servAddr->sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr->sin_port = htons(PORT);
}

void bindSocket(int sockfd, SA* addr) {
    if ( bind(sockfd, addr, sizeof(*addr)) != 0 ) {
        printf("Error in binding socket\n");
        exit(1);
    }
    printf("Socket successfully binded...\n");
}

void setListenMode(int const socketfd) {
    if ( listen(socketfd, 5) ) {
        printf("Listen failed...\n");
        exit(1);
    }
    printf("Server listening...\n");
}

int setupServerTCP() {
    int const sockfd = createSocketTCP();
    struct sockaddr_in servAddr;
    configServAddr(&servAddr);
    bindSocket(sockfd, (SA *)&servAddr);
    setListenMode(sockfd);
    return sockfd;
}

void showClientInfo(struct sockaddr_in *client) {
    char *ip_str = convertIPToString(client->sin_addr);
    int port = ntohs(client->sin_port);
    printf("Client IP: %s\n", ip_str);
    printf("Client Port: %d\n\n", port);
    free(ip_str);
}

int waitingForAccept(int const sockfd, Broadcast *broadcast) {
    struct sockaddr_in client;
    int lenClient = sizeof(client);
    const int connfd = accept(sockfd, (SA *) &client, &lenClient);
    if ( connfd < 0 ) {
        printf("Server accept failed...\n");
        exit(1);
    }
    printf("Server accept the client:\n");
    showClientInfo(&client);

    if (addClient(broadcast, client, connfd) == -1) {
        char *ip_str = malloc(INET_ADDRSTRLEN);
        inet_ntop(AF_INET, &(client.sin_addr), ip_str, INET_ADDRSTRLEN);
        printf("It wasn't possible to add client from %s to broadcast", ip_str);
    }

    return connfd;
}

void *handleThreadableConnection(void *args) {
    int* connfd = args;
    handleConnection(*connfd);
    return NULL;
}

void handleConnection(int const connfd) {
    char buff[MAX];

    for(;;) {
        memset(buff, 0, MAX);
        recv(connfd, buff, MAX, 0);
        printf("From client: %s\n", buff);
        memset(buff, 0, MAX);
        //broadcastMessage(broadcast, buff, sizeof(buff));
        if (strncmp("exit", buff, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}
