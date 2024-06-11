/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_player_execute
*/

#include "amber_command_graphical.h"

void amber_graphic_execute_tna(UNUSED command_t *cmd, amber_client_t *client,
    amber_world_t *world, UNUSED list_t *clients)
{
    for (int i = 0; world->_teams_name[i]; i++) {
        dprintf(client->_tcp._fd, "tna %s\n", world->_teams_name[i]);
    }
}

void amber_graphic_execute_ppo(command_t *cmd, amber_client_t *client,
    UNUSED amber_world_t *world, list_t *clients)
{
    int id = atoi(cmd->_arg);
    amber_client_t *tmp = amber_get_client_by_id(clients, id);

    if (!tmp) {
        dprintf(client->_tcp._fd, "sbp\n");
        return;
    }
    dprintf(client->_tcp._fd, "ppo %d %d %d %d\n", tmp->_id, tmp->_x, tmp->_y,
        tmp->_direction);
}

void amber_graphic_execute_plv(command_t *cmd, amber_client_t *client,
    UNUSED amber_world_t *world, list_t *clients)
{
    int id = atoi(cmd->_arg);
    amber_client_t *tmp = amber_get_client_by_id(clients, id);

    if (!tmp) {
        dprintf(client->_tcp._fd, "sbp\n");
        return;
    }
    dprintf(client->_tcp._fd, "plv %d %d\n", tmp->_id, tmp->_level);
}

void amber_graphic_execute_pin(command_t *cmd, amber_client_t *client,
    UNUSED amber_world_t *world, list_t *clients)
{
    int id = atoi(cmd->_arg);
    amber_client_t *tmp = amber_get_client_by_id(clients, id);

    if (!tmp) {
        dprintf(client->_tcp._fd, "sbp\n");
        return;
    }
    dprintf(client->_tcp._fd, "pin %d %d %d %d %d %d %d %d %d %d\n", tmp->_id,
        tmp->_x, tmp->_y, tmp->_inventory->_food, tmp->_inventory->_linemate,
        tmp->_inventory->_deraumere, tmp->_inventory->_sibur,
        tmp->_inventory->_mendiane, tmp->_inventory->_phiras,
        tmp->_inventory->_thystame);
}
