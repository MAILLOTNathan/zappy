/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_serv_map
*/

#include "amber_command_server.h"

void amber_serv_map(UNUSED amber_serv_t *server, amber_world_t *world,
    char **cmd)
{
    if (cmd[1] && !strcmp(cmd[1], "-v")) {
        amber_display_world(world, true);
    } else {
        amber_display_world(world, false);
    }
}
