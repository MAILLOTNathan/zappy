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
    amber_client_t *client = NULL;

    for (linked_list_t *tmp = clients; tmp; tmp = tmp->next) {
        client = (amber_client_t *)tmp->data;
        if (client->_queue_command == NULL)
            continue;
        if (client->_queue_command->_command->_id != T_INCANTATION &&
            client->_is_incantating)
            continue;
        update_time(client);
        c_time = client->_queue_command->_command->_time;
        if (c_time <= s_time || s_time == 0) {
            shortest = client;
            s_time = c_time;
        }
    }
    return shortest;
}

static void remove_waiting_clock(linked_list_t *clients, amber_world_t *world)
{
    amber_client_t *client = NULL;

    for (linked_list_t *tmp = clients; tmp; tmp = tmp->next) {
        client = (amber_client_t *)tmp->data;
        if (client->_queue_command == NULL)
            continue;
        if (client->_queue_command->_command == NULL)
            continue;
        client->_queue_command->_command->_time = real_clamp(0,
        client->_queue_command->_command->_time - world->_clock, 10000);
    }
    world->_clock = 20;
}

void amber_logic_loop(amber_serv_t *serv, amber_world_t *world)
{
    linked_list_t *clients = NULL;
    amber_client_t *tmp = NULL;

    while (true) {
        clients = serv->_clients->nodes;
        tmp = get_shortest_client_command(clients);
        if (tmp == NULL)
            break;
        world->_clock -= world->_clock > tmp->_queue_command->_command->_time ?
        tmp->_queue_command->_command->_time : 0;
        if (world->_clock <= tmp->_queue_command->_command->_time) {
            usleep((world->_clock * 1000000) / world->_freq);
            amber_check_client_alive(serv, world);
            amber_refill_world(world);
            remove_waiting_clock(serv->_clients->nodes, world);
            continue;
        }
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
    {T_EJECT, &amber_logic_eject},
    {T_FORK, &amber_logic_fork},
    {T_CONNECT_NBR, &amber_logic_connect_nbr},
    {T_TAKE, &amber_logic_take},
    {T_SET, &amber_logic_set},
    {T_INCANTATION, &amber_logic_incantation},
    {-1, NULL}
};