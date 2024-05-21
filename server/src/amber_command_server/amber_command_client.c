/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_client
*/

#include "amber_command_server.h"

void amber_serv_clients(amber_serv_t *server, UNUSED amber_world_t *world,
    UNUSED char *buffer)
{
    linked_list_t *tmp = server->_clients->nodes;
    amber_client_t *client = NULL;

    printf("[AMBER COMMAND] /clients\n");
    while (tmp) {
        client = (amber_client_t *)tmp->data;
        printf("Client ID: %d | Team: %s | Position: %d %d | Level: %d\n",
            client->_id, client->_team_name, client->_x,
            client->_y, client->_level);
        tmp = tmp->next;
    }
}
