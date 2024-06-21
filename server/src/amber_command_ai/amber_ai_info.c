/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_ai_info
*/

#include "amber_manage_command_ai.h"

void amber_ai_look(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&TRANTOR(client)->_queue_command, NULL, 7, T_LOOK);
}

void amber_ai_inventory(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&TRANTOR(client)->_queue_command, NULL, 1, T_INVENTORY);
}

void amber_ai_connect_nbr(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&TRANTOR(client)->_queue_command, NULL, 0,
        T_CONNECT_NBR);
}
