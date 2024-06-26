/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_event_egg
*/

#include "amber_command_graphical.h"

void amber_send_egg_on_connection(amber_net_cli_t *client, list_t *egg)
{
    linked_list_t *tmp = egg->nodes;
    egg_t *egg_tmp = NULL;

    while (tmp) {
        egg_tmp = (egg_t *)tmp->data;
        snprintfizer(client, "enw #%d #-1 %d %d", egg_tmp->_id,
            egg_tmp->_x, egg_tmp->_y);
        tmp = tmp->next;
    }
}

void amber_event_enw(amber_net_cli_t *client, list_t *gra_client, int id_egg)
{
    linked_list_t *tmp = gra_client->nodes;
    amber_net_cli_t *gra = NULL;
    amber_trantor_t *trantor = TRANTOR(client);

    while (tmp) {
        gra = (amber_net_cli_t *)tmp->data;
        snprintfizer(gra, "enw #%d #%d %d %d", id_egg, trantor->_id,
            trantor->_x, trantor->_y);
        tmp = tmp->next;
    }
}

void amber_event_edi(list_t *gra_client, egg_t *egg)
{
    linked_list_t *tmp = gra_client->nodes;
    amber_net_cli_t *gra = NULL;

    while (tmp) {
        gra = (amber_net_cli_t *)tmp->data;
        snprintfizer(gra, "edi #%d", egg->_id);
        tmp = tmp->next;
    }
}
