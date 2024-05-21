/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_listening
*/

#include "amber_process.h"
#include "amber_manage_client.h"

void amber_waiting_select(amber_serv_t *server)
{
    struct timeval tv = {0, 0};

    if (select(FD_SETSIZE, &server->_readfds, NULL, NULL, &tv) == -1) {
        perror("select");
        server->_is_running = false;
    }
}

void amber_init_fd(amber_serv_t *server)
{
    linked_list_t *tmp = server->_clients->nodes;

    FD_ZERO(&server->_readfds);
    FD_SET(server->_tcp._fd, &server->_readfds);
    while (tmp) {
        FD_SET(((amber_client_t *)tmp->data)->_tcp._fd, &server->_readfds);
        tmp = tmp->next;
    }
}

void amber_accept_client(amber_serv_t *server)
{
    int new_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    new_fd = accept(server->_tcp._fd, (struct sockaddr *)&addr, &addrlen);
    if (new_fd == -1) {
        printf("[AMBER ERROR] Accept failed\n");
        return;
    }
    push_front_list(server->_clients, new_fd);
    printf("[AMBER INFO] New client connected\n");
}

void amber_manage_client(amber_serv_t *server)
{
    linked_list_t *node = server->_clients->nodes;
    linked_list_t *ref = server->_clients->nodes;
    int len = list_len(server->_clients);
    amber_client_t *client = NULL;

    for (int i = 0; i < len; i++) {
        client = CAST(amber_client_t *, node->data);
        ref = node->next;
        if (FD_ISSET(client->_tcp._fd, &server->_readfds))
            amber_manage_client_read(server, client);
        node = ref;
    }
}

void amber_listening(amber_serv_t *server)
{
    while (server->_is_running) {
        amber_init_fd(server);
        amber_waiting_select(server);
        if (FD_ISSET(server->_tcp._fd, &server->_readfds))
            amber_accept_client(server);
        amber_manage_client(server);
    }
}
