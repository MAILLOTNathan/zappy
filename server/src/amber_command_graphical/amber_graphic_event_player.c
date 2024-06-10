/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_event_player
*/

#include "amber_command_graphical.h"

static char get_direction(direction_t direction)
{
    switch (direction) {
    case UP:
        return 'N';
    case DOWN:
        return 'S';
    case LEFT:
        return 'W';
    case RIGHT:
        return 'E';
    }
    return 'N';
}

void amber_event_pnw(amber_client_t *client, list_t *clients_gra)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        dprintf(gra->_tcp._fd, "pnw #%d %d %d %c %d %s\n",
        client->_id, client->_x, client->_y, get_direction(client->_direction),
        client->_level, client->_team_name);
        tmp = tmp->next;
    }
}

void amber_event_pex(amber_client_t *client, list_t *clients_gra)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        dprintf(gra->_tcp._fd, "pex #%d\n", client->_id);
        tmp = tmp->next;
    }
}

void amber_event_pbc(amber_client_t *client, list_t *clients_gra)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        dprintf(gra->_tcp._fd, "pcb #%d %s\n", client->_id, client->_queue_command->_command->_arg);
        tmp = tmp->next;
    }
}

void amber_event_idmoved(amber_client_t *client, list_t *clients_gra, char c)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        dprintf(gra->_tcp._fd, "idm %d %c\n", client->_id, c);
        tmp = tmp->next;
    }
}

void amber_event_pic(amber_client_t *client, amber_serv_t *clients_gra)
{
    linked_list_t *tmp = clients_gra->_graphic_clients->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        dprintf(gra->_tcp._fd, "pic %d %d %d", client->_x, client->_y, (client->_level + 1));
        tmp = tmp->next;
    }
}
