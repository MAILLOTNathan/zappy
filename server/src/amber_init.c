/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_init
*/

#include "amber_init.h"
#include "amber_manage_client.h"

static bool bind_server(amber_serv_t *server)
{
    if (bind(server->_tcp._fd, (struct sockaddr *)&server->_tcp._addr,
        sizeof(server->_tcp._addr)) == -1) {
        perror("bind");
        amber_destroy_server(server);
        return false;
    }
    return true;
}

static bool listen_server(amber_serv_t *server)
{
    if (listen(server->_tcp._fd, SOMAXCONN) == -1) {
        perror("listen");
        amber_destroy_server(server);
        return false;
    }
    return true;
}

amber_serv_t *init_server_tcp(amber_serv_t *server)
{
    server->_tcp._fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->_tcp._fd == -1) {
        perror("socket");
        amber_destroy_server(server);
        exit(84);
    }
    server->_tcp._addr.sin_family = AF_INET;
    server->_tcp._addr.sin_addr.s_addr = INADDR_ANY;
    server->_tcp._addr.sin_port = htons(server->_tcp._port);
    if (bind_server(server) == false)
        exit(84);
    if (listen_server(server) == false)
        exit(84);
    return server;
}

amber_serv_t *amber_create_server(args_t *args)
{
    amber_serv_t *server = calloc(1, sizeof(amber_serv_t));

    if (!server)
        return NULL;
    server->_freq = args->_freq;
    server->_tcp._port = args->_port;
    server->_is_running = true;
    server->_teams_name = args->_teams;
    server->_debug_client._fd = -1;
    server->_clients = create_list(&amber_create_client,
    &amber_destroy_client);
    server->_graphic_clients = create_list(&amber_create_client,
    &amber_destroy_client);
    FD_ZERO(&server->_readfds);
    init_server_tcp(server);
    printf("[AMBER INFO] Server started on port %d\n", server->_tcp._port);
    return server;
}

void amber_destroy_server(amber_serv_t *server)
{
    if (server->_tcp._fd != -1)
        close(server->_tcp._fd);
    destroy_list(&server->_clients);
    free_string_array(server->_teams_name);
    free(server);
    printf("[AMBER INFO] Server stopped\n");
}
