/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_ai_action
*/

#include "amber_manage_command_ai.h"

void amber_ai_broadcast(amber_client_t *client, char **arg)
{
    if (length_string_array(arg) != 2) {
        dprintf(client->_tcp._fd, "ko\n");
        return;
    }
    queue_push_back_d(&client->_queue_command, strdup(arg[1]), 7, T_BROADCAST);
}
