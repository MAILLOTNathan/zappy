/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_event_egg
*/

#include "amber_command_graphical.h"

void amber_event_enw(amber_client_t *client, list_t *gra_client, int id_egg)
{
    linked_list_t *tmp = gra_client->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        dprintf(gra->_tcp._fd, "enw #%d #%d %d %d\n", id_egg, client->_id,
            client->_x, client->_y);
        tmp = tmp->next;
    }
}
