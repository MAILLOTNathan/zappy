/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_listening
*/

#include "amber_process.h"
#include "amber_manage_client.h"
#include "amber_command_server.h"
#include "amber_logic.h"
#include "amber_command_graphical.h"

static void amber_waiting_select(amber_serv_t *server)
{
    if (select(FD_SETSIZE, &server->_readfds, &server->_writefds,
        &server->_exceptfds, NULL) == -1) {
        perror("select");
        server->_is_running = false;
    }
}

void amber_init_fd(amber_serv_t *server)
{
    linked_list_t *tmp = server->_clients->nodes;

    FD_ZERO(&server->_readfds);
    FD_ZERO(&server->_writefds);
    FD_ZERO(&server->_exceptfds);
    FD_SET(server->_tcp._fd, &server->_readfds);
    if (server->_debug_client._fd != -1)
        FD_SET(server->_debug_client._fd, &server->_readfds);
    while (tmp) {
        FD_SET(((amber_net_cli_t *)tmp->data)->_tcp._fd, &server->_readfds);
        FD_SET(((amber_net_cli_t *)tmp->data)->_tcp._fd, &server->_writefds);
        FD_SET(((amber_net_cli_t *)tmp->data)->_tcp._fd, &server->_exceptfds);
        tmp = tmp->next;
    }
    tmp = server->_graphic_clients->nodes;
    for (tmp = server->_graphic_clients->nodes; tmp; tmp = tmp->next) {
        FD_SET(((amber_net_cli_t *)tmp->data)->_tcp._fd, &server->_readfds);
        FD_SET(((amber_net_cli_t *)tmp->data)->_tcp._fd, &server->_writefds);
        FD_SET(((amber_net_cli_t *)tmp->data)->_tcp._fd, &server->_exceptfds);
    }
}

static void amber_accept_client(amber_serv_t *server, UNUSED
    amber_world_t *world)
{
    int new_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    new_fd = accept(server->_tcp._fd, (struct sockaddr *)&addr, &addrlen);
    if (new_fd == -1) {
        printf("[AMBER ERROR] Accept failed\n");
        return;
    }
    dprintf(new_fd, "WELCOME\n");
    push_back_list(server->_clients, new_fd, UNKNOWN);
    printf("[AMBER INFO] New client connected\n");
}

void amber_manage_client(amber_world_t *world, amber_serv_t *server,
    list_t *clients)
{
    linked_list_t *node = clients->nodes;
    linked_list_t *ref = clients->nodes;
    int len = list_len(clients);
    amber_net_cli_t *client = NULL;

    for (int i = 0; i < len; i++) {
        client = CAST(amber_net_cli_t *, node->data);
        ref = node->next;
        if (FD_ISSET(client->_tcp._fd, &server->_exceptfds)) {
            printf("[AMBER INFO] Client disconnected\n");
            remove_node(&clients, node, true);
        }
        if (FD_ISSET(client->_tcp._fd, &server->_readfds))
            amber_manage_client_read(world, server, client, clients);
        node = ref;
    }
}

void amber_manage_server_command(amber_serv_t *server, amber_world_t *world)
{
    char buffer[1024] = {0};
    size_t len = 0;

    len = read(server->_debug_client._fd, buffer, 1024);
    if (len == 0) {
        printf("[AMBER INFO] Debug client disconnected\n");
        close(server->_debug_client._fd);
        server->_debug_client._fd = -1;
        return;
    }
    buffer[len - 1] = buffer[len - 1] == '\n' ? '\0' : buffer[len - 1];
    amber_manage_command(server, world, buffer);
}

void amber_listening(amber_serv_t *server, amber_world_t *world)
{
    while (server->_is_running) {
        amber_init_fd(server);
        amber_waiting_select(server);
        if (FD_ISSET(server->_tcp._fd, &server->_readfds))
            amber_accept_client(server, world);
        amber_manage_client(world, server, server->_clients);
        amber_manage_client(world, server, server->_graphic_clients);
        amber_graphic_loop(server, world);
        if (FD_ISSET(server->_debug_client._fd, &server->_readfds))
            amber_manage_server_command(server, world);
        amber_logic_loop(server, world);
    }
}
