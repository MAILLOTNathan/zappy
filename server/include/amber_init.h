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
    #include "common_defines.h"
    #include "list.h"
    #include "amber_check_arg.h"
    #include "string_array.h"
    #include "amber_world.h"
    #include "amber_queue_command.h"

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
 * @param _buffer A buffer to store the data received from the client.
 * @param _team_name The name of the team the client belongs to.
 * @param _direction The direction the client is facing.
 * @param _x The x-coordinate of the client.
 * @param _y The y-coordinate of the client.
 * @param _level The level of the client.
 * @param _id The ID of the client.
 * @param _queue_command The queue of commands to be executed by the client.
 * @param _inventory The inventory of the client.
 * @param _elapsed_time The elapsed time since the last command.
 * @param _is_graphical A boolean flag indicating if the client is graphical.
 * @param _is_incantating A boolean flag indicating if the client
 * is incantating.
 */
typedef struct amber_client_s {
    tcp_t _tcp;
    char *_buffer;
    char *_team_name;
    direction_t _direction;
    int _x;
    int _y;
    int _level;
    int _id;
    queue_command_t *_queue_command;
    box_t *_inventory;
    bool _is_graphical;
    bool _is_incantating;
    unsigned long _ellapsed_time;
    unsigned long _clock_food;
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
 * @param _writefds
 * @param _clients The list of clients connected to the server.
 * @param _graphic_clients The list of graphic clients connected to the server.
 * @param _is_running A boolean flag indicating if the server is running.
 * @param _teams_name The names of the teams participating in the game.
 */
typedef struct amber_serv_s {
    tcp_t _tcp;
    int _freq;
    fd_set _readfds;
    fd_set _writefds;
    fd_set _exceptfds;

    list_t *_clients;
    list_t *_graphic_clients;
    bool _is_running;
    char **_teams_name;
    tcp_t _debug_client;
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

/**
 * @brief Pointer to the amber_serv_t server instance.
 */
extern amber_serv_t *server;

#endif /* !AMBER_INIT_H_ */
