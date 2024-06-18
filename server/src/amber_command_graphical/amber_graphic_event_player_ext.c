/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_event_player
*/

#include "amber_command_graphical.h"

static int get_id_ressource(box_t *ressource)
{
    if (ressource->_food > 0)
        return 0;
    if (ressource->_linemate > 0)
        return 1;
    if (ressource->_deraumere > 0)
        return 2;
    if (ressource->_sibur > 0)
        return 3;
    if (ressource->_mendiane > 0)
        return 4;
    if (ressource->_phiras > 0)
        return 5;
    if (ressource->_thystame > 0)
        return 6;
    return -1;
}

void amber_event_pie(amber_client_t *client, list_t *clients_gra, bool success)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;
    char *message = success ? "ok" : "ko";

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        snprintfizer(gra, "pie #%d %d %s", client->_x, client->_y,
            message);
        tmp = tmp->next;
    }
}

void amber_event_pdi(amber_client_t *client, list_t *clients_gra)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        snprintfizer(gra, "pdi #%d", client->_id);
        tmp = tmp->next;
    }
}

void amber_event_pgt(amber_client_t *client, list_t *clients_gra,
    box_t *ressource)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        snprintfizer(gra, "pgt #%d %d", client->_id,
        get_id_ressource(ressource));
        tmp = tmp->next;
    }
}

void amber_event_pdr(amber_client_t *client, list_t *clients_gra,
    box_t *ressource)
{
    linked_list_t *tmp = clients_gra->nodes;
    amber_client_t *gra = NULL;

    while (tmp) {
        gra = (amber_client_t *)tmp->data;
        snprintfizer(gra, "pdr #%d %d", client->_id,
        get_id_ressource(ressource));
        tmp = tmp->next;
    }
}

void amber_event_pfk(amber_client_t *client, amber_serv_t *serv)
{
    linked_list_t *tmp = serv->_graphic_clients->nodes;
    amber_client_t *cli = NULL;

    while (tmp) {
        cli = (amber_client_t *)tmp->data;
        snprintfizer(cli, "pfk #%d", client->_id);
        tmp = tmp->next;
    }
}
