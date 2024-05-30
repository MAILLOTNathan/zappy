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

void amber_ai_eject(amber_client_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 7, T_EJECT);
}

void amber_ai_fork(amber_client_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 42, T_FORK);
}

void amber_ai_take_object(amber_client_t *client, char **arg)
{
    if (length_string_array(arg) != 2) {
        dprintf(client->_tcp._fd, "ko\n");
        return;
    }
    queue_push_back_d(&client->_queue_command, strdup(arg[1]), 7, T_TAKE);
}

void amber_ai_set_object(amber_client_t *client, char **arg)
{
    if (length_string_array(arg) != 2) {
        dprintf(client->_tcp._fd, "ko\n");
        return;
    }
    queue_push_back_d(&client->_queue_command, strdup(arg[1]), 7, T_SET);
}