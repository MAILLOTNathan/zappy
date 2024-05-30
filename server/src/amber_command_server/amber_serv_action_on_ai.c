/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_serv_action_on_ai
*/

#include "amber_command_server.h"
#include "amber_manage_client.h"

void amber_serv_tp(amber_serv_t *server, UNUSED amber_world_t *world,
    char **cmd)
{
    amber_client_t *client = NULL;
    int x = 0;
    int y = 0;

    if (length_string_array(cmd) != 4) {
        printf("Invalid number of arguments\n");
        return;
    }
    x = atoi(cmd[1]);
    y = atoi(cmd[2]);
    client = amber_get_client_by_id(server->_clients, atoi(cmd[3]));
    if (client == NULL) {
        printf("Client %d not found\n", atoi(cmd[3]));
        return;
    }
    client->_x = x;
    client->_y = y;
    printf("Client %d teleported to %d %d\n", client->_id, x, y);
}
