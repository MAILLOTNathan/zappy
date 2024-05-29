/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_broadcast
*/

#include "amber_logic.h"

static int get_direction_message(amber_client_t *src, amber_client_t *des,
    int width, int height)
{
    int distances[2] = {get_distance(src->_x, des->_x, width),
        get_distance(src->_y, des->_y, height)};
    int directions[2] = {get_direction_action(src->_x, des->_x, width),
        get_direction_action(src->_y, des->_y, height)};
    bool *perimeter = NULL;

    perimeter = initialize_perimeter(directions);
    perimeter = precise_perimeter(perimeter, distances);
    return get_direction_by_perimeter(perimeter, src);
}

void amber_logic_broadcast(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_client_t *tmp = NULL;
    linked_list_t *clients = serv->_clients->nodes;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_id == client->_id)
            continue;
        dprintf(tmp->_tcp._fd, "message %d, %s\n",
        get_direction_message(client, tmp, world->_width, world->_height),
        client->_queue_command->_command->_arg);
    }
}
