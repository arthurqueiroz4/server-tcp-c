//
// Created by arthur on 08/07/24.
//
#include "signalHandler.h"

static int server_fd; // Descritor de arquivo do servidor

void *signalHandlerThread(void *arg) {
    sigset_t *set = arg;
    int sig;

    while (1) {
        sigwait(set, &sig);
        printf("Caught signal %d\n", sig);

        close(server_fd);
        printf("Server closed\n");

        exit(0);
    }
}

void setupSignalHandler(int fd) {
    server_fd = fd;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);

    pthread_sigmask(SIG_BLOCK, &set, NULL);

    pthread_t signal_thread;
    if (pthread_create(&signal_thread, NULL, signalHandlerThread, &set) != 0) {
        perror("pthread_create");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
}