#include <pthread.h>
#include <stdlib.h>

#include "src/server.h"
#include "src/signalHandler.h"
#include "src/broadcast.h"
#include "src/utils.h"

int main(void) {
    int const sockfd = setupServerTCP();
    pthread_t thread_id;

    setupSignalHandler(sockfd);

    Broadcast *broadcast = newBroadcast();

    ParamsForThread params;
    params.broadcast = broadcast;

    for (;;) {
        int connfd = waitingForAccept(sockfd, broadcast);
        params.connfd = connfd;
        pthread_create(&thread_id, NULL, handleThreadableConnection, &params);
    }
}
