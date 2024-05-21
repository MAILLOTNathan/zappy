/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_client
*/

#include "amber_manage_client.h"
#include "list.h"

void *amber_create_client(va_list *ap)
{
    amber_client_t *client = calloc(1, sizeof(amber_client_t));

    if (!client)
        return NULL;
    client->_tcp._fd = va_arg(*ap, int);
    return client;
}

void amber_destroy_client(void *client)
{
    amber_client_t *tmp = (amber_client_t *)client;

    close(tmp->_tcp._fd);
    free(tmp);
}

static bool cmp(void *data, void *data_ref)
{
    return (data == data_ref);
}

void amber_manage_client_read(amber_serv_t *server, amber_client_t *client)
{
    char buffer[1024] = {0};
    int valread = read(client->_tcp._fd, buffer, 1024);

    if (valread == 0) {
        printf("[AMBER INFO] Client disconnected\n");
        remove_node(&server->_clients, list_find_node(
        server->_clients, client, cmp));
        return;
    }
    printf("[AMBER INFO] Message received: %s\n", buffer);
    // Handle the message here
}
