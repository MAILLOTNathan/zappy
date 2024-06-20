/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_player_execute
*/

#include "amber_command_graphical.h"

static char get_direction(direction_t direction)
{
    switch (direction) {
    case UP:
        return 'N';
    case DOWN:
        return 'S';
    case LEFT:
        return 'W';
    case RIGHT:
        return 'E';
    }
    return 'N';
}

void amber_graphic_execute_tna(UNUSED command_t *cmd, amber_net_cli_t *client,
    amber_world_t *world, UNUSED list_t *clients)
{
    for (int i = 0; world->_teams_name[i]; i++) {
        snprintfizer(client, "tna %s", world->_teams_name[i]);
    }
}

void amber_graphic_execute_ppo(command_t *cmd, amber_net_cli_t *client,
    UNUSED amber_world_t *world, list_t *clients)
{
    int id = atoi(cmd->_arg + 1);
    amber_net_cli_t *tmp = amber_get_client_by_id(clients, id);

    if (!tmp) {
        snprintfizer(client, "sbp ppo");
        return;
    }
    snprintfizer(client, "ppo #%d %d %d %c", tmp->_id, TRANTOR(tmp)->_x,
        TRANTOR(tmp)->_y, get_direction(TRANTOR(tmp)->_direction));
}

void amber_graphic_execute_plv(command_t *cmd, amber_net_cli_t *client,
    UNUSED amber_world_t *world, list_t *clients)
{
    int id = atoi(cmd->_arg + 1);
    amber_net_cli_t *tmp = amber_get_client_by_id(clients, id);

    if (!tmp) {
        snprintfizer(client, "sbp plv");
        return;
    }
    snprintfizer(client, "plv #%d %d", TRANTOR(tmp)->_id,
        TRANTOR(tmp)->_level);
}

void amber_graphic_execute_pin(command_t *cmd, amber_net_cli_t *client,
    UNUSED amber_world_t *world, list_t *clients)
{
    int id = atoi(cmd->_arg + 1);
    amber_net_cli_t *tmp = amber_get_client_by_id(clients, id);
    amber_trantor_t *trantor;

    if (!tmp) {
        snprintfizer(client, "sbp pin");
        return;
    }
    trantor = TRANTOR(tmp);
    snprintfizer(client, "pin #%d %d %d %d %d %d %d %d %d %d",
        tmp->_id,
        trantor->_x, trantor->_y, trantor->_inventory->_food,
        trantor->_inventory->_linemate,
        trantor->_inventory->_deraumere, trantor->_inventory->_sibur,
        trantor->_inventory->_mendiane, trantor->_inventory->_phiras,
        trantor->_inventory->_thystame);
}
