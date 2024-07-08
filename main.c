#include "src/server.h"


int main(void) {
    int const sockfd = setupServerTCP();

    for (;;) {
        int connfd = waitingForAccept(sockfd);
        handleConnection(connfd);
    }
}
