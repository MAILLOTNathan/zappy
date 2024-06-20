/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_ai_forward
*/

#include "amber_manage_command_ai.h"

void amber_ai_forward(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&TRANTOR(client)->_queue_command, NULL, 7, T_FORWARD);
}

void amber_ai_incantation(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&TRANTOR(client)->_queue_command, NULL, 300,
        T_INCANTATION);
}
