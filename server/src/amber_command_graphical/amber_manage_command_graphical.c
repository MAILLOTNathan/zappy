/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_command_graphical
*/

#include "amber_command_graphical.h"

void amber_manage_command_grahical(amber_client_t *client, char **arg)
{
    for (int i = 0; graphical_commands[i]._command; i++) {
        if (strcmp(graphical_commands[i]._command, arg[0]) == 0) {
            graphical_commands[i]._func(client, arg);
            break;
        }
    }
}

static void check_command(amber_client_t *client, amber_world_t *world,
    queue_command_t *tmp, list_t *clients)
{
    for (int i = 0; graphical_commands[i]._command; i++) {
        if (graphical_commands[i]._id == tmp->_command->_id) {
            graphical_commands[i]._execute(tmp->_command, client, world,
            clients);
            break;
        }
    }
}

void amber_graphic_loop(amber_serv_t *server, amber_world_t *world)
{
    linked_list_t *node = server->_graphic_clients->nodes;
    amber_client_t *client = NULL;
    queue_command_t *tmp = NULL;

    while (node) {
        client = (amber_client_t *)node->data;
        tmp = client->_queue_command;
        while (tmp) {
            check_command(client, world, tmp, server->_clients);
            tmp = tmp->_next;
        }
        queue_destroy(&client->_queue_command);
        node = node->next;
    }
}

const graphical_command_t graphical_commands[] = {
    {"msz", &amber_graphic_msz, &amber_graphic_execute_msz, T_MSZ},
    {"mct", &amber_graphic_mct, &amber_graphic_execute_mct, T_MCT},
    {"bct", &amber_graphic_bct, &amber_graphic_execute_bct, T_BCT},
    {"sgt", &amber_graphic_sgt, &amber_graphic_execute_sgt, T_SGT},
    {"sst", &amber_graphic_sst, &amber_graphic_execute_sst, T_SST},
    {"tna", &amber_graphic_tna, &amber_graphic_execute_tna, T_TNA},
    {"ppo", &amber_graphic_ppo, &amber_graphic_execute_ppo, T_PPO},
    {"plv", &amber_graphic_plv, &amber_graphic_execute_plv, T_PLV},
    {"pin", &amber_graphic_pin, &amber_graphic_execute_pin, T_PIN},
    {NULL, NULL, NULL, -1}
};
