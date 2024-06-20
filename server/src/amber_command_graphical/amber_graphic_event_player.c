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

void amber_event_pnw(amber_net_cli_t *client, list_t *clients_gra)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_net_cli_t *gra = NULL;
    amber_trantor_t *trantor = TRANTOR(client);

    while (tmp) {
        gra = (amber_net_cli_t *)tmp->data;
        snprintfizer(gra, "pnw #%d %d %d %c %d %s",
        trantor->_id, trantor->_x, trantor->_y,
            get_direction(trantor->_direction), trantor->_level,
            trantor->_team_name);
        tmp = tmp->next;
    }
}

void amber_event_pex(amber_net_cli_t *client, list_t *clients_gra)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_net_cli_t *gra = NULL;

    while (tmp) {
        gra = (amber_net_cli_t *)tmp->data;
        snprintfizer(gra, "pex #%d", client->_id);
        tmp = tmp->next;
    }
}

void amber_event_pbc(amber_net_cli_t *client, list_t *clients_gra)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_net_cli_t *gra = NULL;
    amber_trantor_t *trantor = TRANTOR(client);

    while (tmp) {
        gra = (amber_net_cli_t *)tmp->data;
        snprintfizer(gra, "pbc #%d %s", trantor->_id,
            trantor->_queue_command->_command->_arg);
        tmp = tmp->next;
    }
}

void amber_event_idmoved(amber_net_cli_t *client, list_t *clients_gra, char c)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_net_cli_t *gra = NULL;

    while (tmp) {
        gra = (amber_net_cli_t *)tmp->data;
        snprintfizer(gra, "idm %d %c", client->_id, c);
        tmp = tmp->next;
    }
}

static void print_ids(int *ids, int i, amber_net_cli_t *cli)
{
    for (int j = 0; j < i; j++) {
        if (ids[j] == -1)
            continue;
        dprintf(cli->_tcp._fd, " #%d", ids[j]);
    }
    dprintf(cli->_tcp._fd, "\n");
}

void amber_event_pic(amber_net_cli_t *client, amber_serv_t *serv, int *ids)
{
    int i = list_len(serv->_clients);
    linked_list_t *tmp = serv->_graphic_clients->nodes;
    amber_net_cli_t *cli = NULL;
    amber_trantor_t *trantor = TRANTOR(client);

    while (tmp) {
        cli = (amber_net_cli_t *)tmp->data;
        dprintf(cli->_tcp._fd, "pic %d %d %d", trantor->_x, trantor->_y,
            trantor->_level);
        print_ids(ids, i, cli);
        tmp = tmp->next;
    }
}
