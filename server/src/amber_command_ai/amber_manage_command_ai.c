/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_command_ai
*/

#include "amber_manage_command_ai.h"

void amber_manage_command_ai(amber_client_t *client, char *buffer)
{
    char **arg = NULL;
    int i = 0;

    if (queue_command_size(client->_queue_command) >= 10) {
        dprintf(client->_tcp._fd, "ko\n");
        return;
    }
    arg = string_to_string_array(buffer);
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
    free_string_array(arg);
}

const ai_command_t ai_commands[] = {
    {"Forward", T_FORWARD, &amber_ai_forward},
    {"Right", T_RIGHT, &amber_ai_right},
    {"Left", T_LEFT, &amber_ai_left},
    {"Look", T_LOOK, &amber_ai_look},
    {NULL, -1, NULL}
};

