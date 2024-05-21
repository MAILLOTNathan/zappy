/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_init
*/

#ifndef AMBER_INIT_H_
    #define AMBER_INIT_H_

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include "commonDefines.h"

typedef struct amber_serv_s {
    int _fd;
    int _port;
    int _freq;
    struct sockaddr_in _addr;
    fd_set _readfds;

} amber_serv_t;

#endif /* !AMBER_INIT_H_ */
