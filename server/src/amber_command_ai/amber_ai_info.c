/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_ai_info
*/

#include "amber_manage_command_ai.h"

void amber_ai_look(amber_client_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 7, T_LOOK);
}
