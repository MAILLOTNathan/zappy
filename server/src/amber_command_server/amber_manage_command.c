/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_command
*/

#include "amber_command_server.h"

void amber_manage_command(amber_serv_t *server, amber_world_t *world,
    char *buffer)
{
    char **cmd = string_to_string_array(buffer);

    if (cmd == NULL)
        return;
    for (int i = 0; command_serv[i].command != NULL; i++) {
        if (strcmp(command_serv[i].command, cmd[0]) == 0) {
            command_serv[i].func(server, world, cmd);
            break;
        }
    }
    free_string_array(cmd);
}


const amber_command_server_t command_serv[] = {
    {"/clients", &amber_serv_clients},
    {"/map", &amber_serv_map},
    {NULL, NULL}
};
