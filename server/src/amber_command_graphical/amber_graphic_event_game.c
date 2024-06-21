/*
** EPITECH PROJECT, 2024
** server
** File description:
** amber_graphic_event_game
*/

#include "amber_command_graphical.h"

void amber_event_seg(list_t *clients, char *teams)
{
    linked_list_t *tmp = clients->nodes;
    amber_net_cli_t *client = NULL;

    while (tmp) {
        client = (amber_net_cli_t *)tmp->data;
        snprintfizer(client, "seg %s", teams);
        tmp = tmp->next;
    }
}
