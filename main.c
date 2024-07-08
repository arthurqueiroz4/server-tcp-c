#include "src/server.h"
#include <pthread.h>

int main(void) {
    int const sockfd = setupServerTCP();
    pthread_t thread_id;

    for (;;) {
        int connfd = waitingForAccept(sockfd);
        pthread_create(&thread_id, NULL, handleThreadableConnection, &connfd);
    }
}
