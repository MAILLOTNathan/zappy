/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_event_player
*/

#include "amber_command_graphical.h"

void amber_event_pie(amber_client_t *client, list_t *clients_gra, bool success)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;
    char *message = success ? "ok" : "ko";

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        dprintf(gra->_tcp._fd, "pie %d %d %s\n", client->_x, client->_y, message);
        tmp = tmp->next;
    }
}

