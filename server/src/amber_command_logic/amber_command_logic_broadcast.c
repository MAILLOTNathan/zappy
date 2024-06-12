/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_broadcast
*/

#include "amber_logic.h"
#include "amber_command_graphical.h"


const int concave[4][8] = {
    {1, 2, 3, 4, 5, 6, 7, 8},
    {3, 4, 5, 6, 7, 8, 1, 2},
    {5, 6, 7, 8, 1, 2, 3, 4},
    {7, 8, 1, 2, 3, 4, 5, 6}
};


static int get_direction_message(amber_client_t *src, amber_client_t *des,
    int width, int height)
{
    pos_t distance = {get_distance(src->_x, des->_x, width),
        get_distance(src->_y, des->_y, height)};
    pos_t start_pos = {src->_x, src->_y};
    pos_t end_pos = {src->_x + distance.x, src->_y + distance.y};
    pos_t end = plotline(&start_pos, &end_pos);

    printf("velocity x: %d, velocity y: %d\n", distance.x, distance.y);
    printf("end distance x: %d, end distance y: %d\n", end_pos.x, end_pos.y);
    printf("BEFORE CLAMP end x: %d, end y: %d\n", end.x, end.y);
    end.x = clamp(0, end.x, width);
    end.y = clamp(0, end.y, height);
    printf("end x: %d, end y: %d\n", end.x, end.y);
    return 0;
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
    amber_event_pbc(client, serv->_graphic_clients);
    send_cli_msg(client, "ok");
}
