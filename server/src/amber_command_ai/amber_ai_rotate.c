/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_ai_right
*/

#include "amber_manage_command_ai.h"

void amber_ai_right(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&TRANTOR(client)->_queue_command, NULL, 7, T_RIGHT);
}

void amber_ai_left(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&TRANTOR(client)->_queue_command, NULL, 7, T_LEFT);
}
