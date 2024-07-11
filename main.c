#include "src/server.h"
#include <pthread.h>

#include "src/signalHandler.h"
#include "src/broadcast.h"

int main(void) {
    int const sockfd = setupServerTCP();
    pthread_t thread_id;

    setupSignalHandler(sockfd);

    Broadcast *broadcast = newBroadcast();

    for (;;) {
        int connfd = waitingForAccept(sockfd, broadcast);
        pthread_create(&thread_id, NULL, handleThreadableConnection, &connfd);
    }
}
