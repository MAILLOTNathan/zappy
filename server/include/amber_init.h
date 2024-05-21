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
    #include "list.h"
    #include "amber_check_arg.h"

/**
 * @brief Represents a TCP connection.
 *
 * The `tcp_t` struct holds information about a TCP connection,
 * including the file descriptor,
 * the port number, and the address.
 *
 * @param _fd The file descriptor of the connection.
 * @param _port The port number of the connection.
 * @param _addr The address of the connection.
 */
typedef struct tcp_s {
    int _fd;
    int _port;
    struct sockaddr_in _addr;
} tcp_t;

/**
 * @brief Structure representing an Amber client.
 *
 * This structure contains the necessary information to handle an Amber client.
 * It includes a TCP connection object.
 *
 * @param _tcp The TCP connection object for the client.
 */
typedef struct amber_client_s {
    tcp_t _tcp;
    char *_buffer;
} amber_client_t;

/**
 * @brief Structure representing the Amber server.
 *
 * This structure holds the necessary information for the Amber server.
 * It includes the TCP connection, the frequency, the file descriptor set,
 * and a list of clients.
 *
 * @param _tcp The TCP connection object for the server.
 * @param _freq The frequency of game cycles.
 * @param _readfds The file descriptor set for the server.
 * @param _clients The list of clients connected to the server.
 * @param _is_running A boolean flag indicating if the server is running.
 */
typedef struct amber_serv_s {
    tcp_t _tcp;
    int _freq;
    fd_set _readfds;

    list_t *_clients;
    bool _is_running;
} amber_serv_t;

/**
 * @brief Creates an Amber server.
 *
 * This function creates and initializes an Amber server
 * based on the provided arguments.
 *
 * @param args The arguments used to configure the server.
 * @return A pointer to the created Amber server.
 */
amber_serv_t *amber_create_server(args_t *args);

/**
 * @brief Destroys an Amber server instance.
 *
 * This function is responsible for cleaning up
 * the resources allocated for an Amber server instance.
 *
 * @param server A pointer to the `amber_serv_t`
 * structure representing the server instance to be destroyed.
 */
void amber_destroy_server(amber_serv_t *server);

extern amber_serv_t *server;

#endif /* !AMBER_INIT_H_ */
