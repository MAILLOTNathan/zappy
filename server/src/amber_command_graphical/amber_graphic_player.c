/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_player
*/

#include "amber_command_graphical.h"

void amber_graphic_tna(amber_client_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 0, T_TNA);
}

void amber_graphic_ppo(amber_client_t *client, char **arg)
{
    if (length_string_array(arg) != 2) {
        dprintf(client->_tcp._fd, "sbp ppo\n");
        return;
    }
    queue_push_back_d(&client->_queue_command, strdup(arg[1]), 0, T_PPO);
}

void amber_graphic_plv(amber_client_t *client, char **arg)
{
    if (length_string_array(arg) != 2) {
        dprintf(client->_tcp._fd, "sbp plv\n");
        return;
    }
    queue_push_back_d(&client->_queue_command, strdup(arg[1]), 0, T_PLV);
}

void amber_graphic_pin(amber_client_t *client, char **arg)
{
    if (length_string_array(arg) != 2) {
        dprintf(client->_tcp._fd, "sbp pin\n");
        return;
    }
    queue_push_back_d(&client->_queue_command, strdup(arg[1]), 0, T_PIN);
}
