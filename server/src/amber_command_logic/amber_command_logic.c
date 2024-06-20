/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic
*/

#include "amber_logic.h"
#include <unistd.h>

static void exec_logic_function(amber_net_cli_t *cli, amber_world_t *wd,
    amber_serv_t *serv, amber_trantor_t *trantor)
{
    if (trantor->_ellapsed_time >= get_time_in_microseconds())
        return;
    for (int i = 0; logic_commands[i]._func != NULL; i++)
        if (trantor->_queue_command->_command->_id == logic_commands[i]._command)
            logic_commands[i]._func(cli, wd, serv);
    queue_pop_front(&trantor->_queue_command);
    if (queue_command_size(trantor->_queue_command) == 0)
        return;
    trantor->_ellapsed_time = get_new_time_in_microseconds(
        trantor->_queue_command->_command->_time / wd->_freq);
}

void amber_logic_loop(amber_serv_t *serv, amber_world_t *world)
{
    linked_list_t *clients = NULL;
    amber_net_cli_t *tmp = NULL;
    amber_trantor_t *trantor = NULL;

    if (world->_clock < get_time_in_microseconds())
        amber_refill_world(world);
    amber_check_client_alive(serv, world);
    clients = serv->_clients->nodes;
    for (; clients; clients = clients->next) {
        tmp = (amber_net_cli_t *)clients->data;
        if (tmp->_type != AI)
            continue;
        trantor = TRANTOR(tmp);
        if (trantor->_queue_command == NULL)
            continue;
        if (trantor->_is_incantating &&
        trantor->_queue_command->_command->_id != T_INCANTATION)
            continue;
        exec_logic_function(trantor, world, serv);
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
