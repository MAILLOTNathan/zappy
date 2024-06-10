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
    if (cli->_ellapsed_time >= get_time_in_microseconds())
        return;
    for (int i = 0; logic_commands[i]._func != NULL; i++)
        if (cli->_queue_command->_command->_id == logic_commands[i]._command)
            logic_commands[i]._func(cli, wd, serv);
    queue_pop_front(&cli->_queue_command);
    if (queue_command_size(cli->_queue_command) == 0)
        return;
    cli->_ellapsed_time = get_new_time_in_microseconds(
        cli->_queue_command->_command->_time / wd->_freq);
}

void amber_logic_loop(amber_serv_t *serv, amber_world_t *world)
{
    linked_list_t *clients = NULL;
    amber_client_t *tmp = NULL;

    if (world->_clock >= get_time_in_microseconds())
        amber_refill_world(world);
    amber_check_client_alive(serv, world);
    clients = serv->_clients->nodes;
    for (; clients; clients = clients->next) {
        tmp = (amber_client_t *)clients->data;
        if (tmp->_queue_command == NULL)
            continue;
        if (tmp->_is_incantating &&
        tmp->_queue_command->_command->_id != T_INCANTATION)
            continue;
        if (!tmp->_queue_command || tmp->_team_name == NULL)
            continue;
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
