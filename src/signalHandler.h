//
// Created by arthur on 08/07/24.
//

#ifndef HANDLESIGNAL_H
#define HANDLESIGNAL_H

#include <signal.h>

// Função para inicializar a thread de tratamento de sinais
void setupSignalHandler(int server_fd);

#endif //HANDLESIGNAL_H
