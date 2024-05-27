/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic
*/

#include "amber_logic.h"
#include <unistd.h>

static void exec_logic_function(amber_client_t *cli, amber_world_t *wd,
    amber_serv_t *serv)
{
    linked_list_t *clients = serv->_clients->nodes;
    command_t *command = cli->_queue_command->_command;
    amber_client_t *client = NULL;

    usleep((command->_time * 1000000) / wd->_freq);
    for (int i = 0; logic_commands[i]._func != NULL; i++)
        if (cli->_queue_command->_command->_id == logic_commands[i]._command)
            logic_commands[i]._func(cli, wd, serv);
    for (linked_list_t *tmp = clients; tmp; tmp = tmp->next) {
        client = (amber_client_t *)tmp->data;
        if (client->_queue_command == NULL) {
            client->_elapsed_time += command->_time;
            continue;
        }
        client->_queue_command->_command->_time = real_clamp(0,
        client->_queue_command->_command->_time - command->_time, 10000);
    }
    queue_pop_front(&cli->_queue_command);
}

static void update_time(amber_client_t *client)
{
    int time = 0;

    if (client->_elapsed_time == 0)
        return;
    for (queue_command_t *tmp = client->_queue_command; tmp;
        tmp = tmp->_next) {
        time = tmp->_command->_time;
        tmp->_command->_time = real_clamp(0, time - client->_elapsed_time,
        10000);
        client->_elapsed_time = real_clamp(0, client->_elapsed_time - time,
        10000);
        if (client->_elapsed_time == 0)
            return;
    }
}

static amber_client_t *get_shortest_client_command(linked_list_t *clients)
{
    amber_client_t *shortest = NULL;
    int s_time = 0;
    int c_time = 0;

    for (linked_list_t *tmp = clients; tmp; tmp = tmp->next) {
        if (((amber_client_t *)tmp->data)->_queue_command == NULL)
            continue;
        if (((amber_client_t *)tmp->data)->_queue_command->_command == NULL)
            continue;
        update_time(((amber_client_t *)tmp->data));
        c_time = ((amber_client_t *)tmp->data)
        ->_queue_command->_command->_time;
        if (c_time <= s_time || s_time == 0) {
            shortest = ((amber_client_t *)tmp->data);
            s_time = c_time;
        }
    }
    return shortest;
}

void amber_logic_loop(amber_serv_t *serv, amber_world_t *world)
{
    linked_list_t *clients = serv->_clients->nodes;
    amber_clock_t clock = {._start = 0, ._end = 0};
    amber_client_t *tmp = NULL;

    amber_clock_start(&clock);
    while (true) {
        tmp = get_shortest_client_command(clients);
        if (tmp == NULL)
            return;
        exec_logic_function(tmp, world, serv);
    }
}

const logic_command_t logic_commands[] = {
    {T_FORWARD, &amber_logic_forward},
    {T_RIGHT, &amber_logic_right},
    {T_LEFT, &amber_logic_left},
    {T_LOOK, &amber_logic_look},
    {T_INVENTORY, &amber_logic_inventory},
    {T_BROADCAST, &amber_logic_broadcast},
    {-1, NULL}
};
