/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_command_ai
*/

#include "amber_manage_command_ai.h"

void amber_manage_command_ai(amber_client_t *client, char **arg)
{
    int i = 0;

    if (queue_command_size(client->_queue_command) >= 10) {
        dprintf(client->_tcp._fd, "ko\n");
        return;
    }
    for (i = 0; ai_commands[i]._command; i++) {
        if (strcmp(ai_commands[i]._command, arg[0]) == 0) {
            ai_commands[i]._func(client, arg);
            break;
        }
    }
    if (ai_commands[i]._command == NULL)
        dprintf(client->_tcp._fd, "ko\n");
    else
        printf("[AMBER AI] Command recevei %s\n", arg[0]);
}

const ai_command_t ai_commands[] = {
    {"Forward", T_FORWARD, &amber_ai_forward},
    {"Right", T_RIGHT, &amber_ai_right},
    {"Left", T_LEFT, &amber_ai_left},
    {"Look", T_LOOK, &amber_ai_look},
    {"Inventory", T_INVENTORY, &amber_ai_inventory},
    {"Connect_nbr", T_CONNECT_NBR, &amber_ai_connect_nbr},
    {"Broadcast", T_BROADCAST, &amber_ai_broadcast},
    {"Eject", T_EJECT, &amber_ai_eject},
    {"Fork", T_FORK, &amber_ai_fork},
    {"Take", T_TAKE, &amber_ai_take_object},
    {"Set", T_SET, &amber_ai_set_object},
    {NULL, -1, NULL}
};
