#include "src/server.h"
#include <pthread.h>

#include "src/signalHandler.h"

int main(void) {
    int const sockfd = setupServerTCP();
    pthread_t thread_id;

    setupSignalHandler(sockfd);

    for (;;) {
        int connfd = waitingForAccept(sockfd);
        pthread_create(&thread_id, NULL, handleThreadableConnection, &connfd);
    }
}
