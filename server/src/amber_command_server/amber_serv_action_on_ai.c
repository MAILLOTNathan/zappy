/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_serv_action_on_ai
*/

#include "amber_command_server.h"
#include "amber_manage_client.h"

static void update_world(amber_world_t *world, amber_trantor_t *trantor,
    int x, int y)
{
    world->_case[trantor->_y][trantor->_x]._players--;
    trantor->_x = x;
    trantor->_y = y;
    world->_case[trantor->_y][trantor->_x]._players++;
}

void amber_serv_tp(amber_serv_t *serv, amber_world_t *world,
    char **cmd)
{
    amber_net_cli_t *client = NULL;
    int x = 0;
    int y = 0;

    if (length_string_array(cmd) != 4) {
        dprintf(FDDEBUG(serv), "Invalid number of arguments\n");
        return;
    }
    x = atoi(cmd[1]);
    y = atoi(cmd[2]);
    client = amber_get_client_by_id(serv->_clients, atoi(cmd[3]));
    if (client == NULL) {
        dprintf(FDDEBUG(serv), "Client %d not found\n", atoi(cmd[3]));
        return;
    }
    update_world(world, TRANTOR(client), x, y);
    dprintf(FDDEBUG(serv), "Client %d teleported to %d %d\n",
    client->_id, x, y);
}
