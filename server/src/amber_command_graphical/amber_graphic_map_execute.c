/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_map_execute
*/

#include "amber_command_graphical.h"
#include "amber_logic.h"

void amber_graphic_execute_msz(UNUSED command_t *cmd, amber_client_t *client,
    amber_world_t *world, UNUSED list_t *clients)
{
    dprintf(client->_tcp._fd, "msz %d %d\n", world->_width, world->_height);
}

void amber_graphic_execute_mct(UNUSED command_t *cmd, amber_client_t *client,
    amber_world_t *world, UNUSED list_t *clients)
{
    for (int i = 0; world->_height > i; i++) {
        for (int j = 0; world->_width > j; j++) {
            dprintf(client->_tcp._fd, CONTANT_MAP, j, i,
                world->_case[i][j]._food,
                world->_case[i][j]._linemate, world->_case[i][j]._deraumere,
                world->_case[i][j]._sibur, world->_case[i][j]._mendiane,
                world->_case[i][j]._phiras, world->_case[i][j]._thystame);
        }
    }
}

void amber_graphic_execute_bct(command_t *cmd, amber_client_t *client,
    amber_world_t *world, UNUSED list_t *clients)
{
    char **arg = string_to_string_array(cmd->_arg);
    int x = atoi(arg[0]);
    int y = atoi(arg[1]);

    x = clamp(0, x, world->_width);
    x = x == world->_width ? 0 : x;
    y = clamp(0, y, world->_height);
    y = y == world->_height ? 0 : y;
    dprintf(client->_tcp._fd, CONTANT_MAP, x, y,
        world->_case[y][x]._food,
        world->_case[y][x]._linemate, world->_case[y][x]._deraumere,
        world->_case[y][x]._sibur, world->_case[y][x]._mendiane,
        world->_case[y][x]._phiras, world->_case[y][x]._thystame);
}

void amber_graphic_execute_sgt(UNUSED command_t *cmd, amber_client_t *client,
    amber_world_t *world, UNUSED list_t *clients)
{
    dprintf(client->_tcp._fd, "sgt %f\n", world->_freq);
}

void amber_graphic_execute_sst(command_t *cmd, amber_client_t *client,
    amber_world_t *world, UNUSED list_t *clients)
{
    double freq = atof(cmd->_arg);

    if (freq <= 0)
        return;
    world->_freq = freq;
    dprintf(client->_tcp._fd, "sst %f\n", world->_freq);
}
