//
// Created by arthur on 11/07/24.
//

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

char *
convertIPToString(struct in_addr sin_addr);


#endif //UTILS_H
