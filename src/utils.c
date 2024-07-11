//
// Created by arthur on 11/07/24.
//

#include "utils.h"

char *convertIPToString(struct in_addr sin_addr) {
    char *ip_str = malloc(INET_ADDRSTRLEN);

    inet_ntop(AF_INET, &sin_addr, ip_str, INET_ADDRSTRLEN);

    return ip_str;
}
