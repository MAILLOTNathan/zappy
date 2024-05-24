/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic
*/

#include "amber_logic.h"

static void exec_logic_function(amber_client_t *cli, amber_world_t *wd)
{
    for (int i = 0; logic_commands[i]._command != -1; i++)
        if (cli->_queue_command->_command == logic_commands[i]._command)
            return logic_commands[i]->_func(cli, wd);
}

static amber_client_t *get_shortest_client_command(linked_list_t *clients)
{
    amber_client_t *shortest = NULL;
    int s_time = 0;
    int c_time = 0;

    for (linked_list_t *tmp = clients; tmp; tmp = tmp->next) {
        c_time = ((amber_client_t *)tmp->data)->_queue_command->_command->_time;
        if (c_time < s_time && s_time >= 0)
            shortest = ((amber_client_t *)tmp->data);
    }
    return shortest;
}

void amber_logic_loop(amber_serv_t *serv, amber_world_t *world)
{
    linked_list_t *clients = serv->_clients->nodes;
    amber_clock_t clock = {._start = 0, _stop = 0};

    amber_clock_start(&clock);
    while (clients) {
        exec_logic_function(get_shortest_client_command(clients), world);
        clients = clients->next;
    }
}

const logic_command_t *logic_commands[] = {
    {T_FORWARD, &amber_logic_forward},
    {T_RIGHT, &amber_logic_right},
    {T_LEFT, &amber_logic_left},
    {T_LOOK, &amber_logic_look},
    {T_INVENTORY, &amber_logic_inventory},
    // {T_BROADCAST, &amber_logic_broadcast},
    {-1, NULL}
}