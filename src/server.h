//
// Created by arthur on 07/07/24.
//

#ifndef SERVER_H
#define SERVER_H

int
setupServerTCP();

int
waitingForAccept(int fd);

void
handleConnection(int fd);

#endif //SERVER_H
