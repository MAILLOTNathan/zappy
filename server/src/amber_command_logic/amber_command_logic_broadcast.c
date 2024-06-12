/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_broadcast
*/

#include "amber_logic.h"
#include "amber_command_graphical.h"


static const int concave[4][8] = {
    {1, 2, 3, 4, 5, 6, 7, 8},
    {3, 4, 5, 6, 7, 8, 1, 2},
    {5, 6, 7, 8, 1, 2, 3, 4},
    {7, 8, 1, 2, 3, 4, 5, 6}
};


int get_broadcast_angle(pos_t *vel, amber_client_t *des)
{
    if (vel->x == 0 && vel->y == 0)
        return 0;
    if (vel->x == -1 && vel->y == -1)
        return concave[des->_direction - 1][1];
    if (vel->x == -1 && vel->y == 0)
        return concave[des->_direction - 1][2];
    if (vel->x == -1 && vel->y == 1)
        return concave[des->_direction - 1][3];
    if (vel->x == 0 && vel->y == -1)
        return concave[des->_direction - 1][0];
    if (vel->x == 0 && vel->y == 1)
        return concave[des->_direction - 1][4];
    if (vel->x == 1 && vel->y == -1)
        return concave[des->_direction - 1][7];
    if (vel->x == 1 && vel->y == 0)
        return concave[des->_direction - 1][6];
    if (vel->x == 1 && vel->y == 1)
        return concave[des->_direction - 1][5];
    return -1;
}

static int get_direction_message(amber_client_t *src, amber_client_t *des,
    int width, int height)
{
    pos_t distance = {get_distance(src->_x, des->_x, width),
        get_distance(src->_y, des->_y, height)};
    pos_t start_pos = {src->_x, src->_y};
    pos_t end_pos = {src->_x + distance.x, src->_y + distance.y};
    pos_t end = plotline(&start_pos, &end_pos);
    pos_t vel = {0, 0};

    printf("velocity x: %d, velocity y: %d\n", distance.x, distance.y);
    printf("end distance x: %d, end distance y: %d\n", end_pos.x, end_pos.y);
    printf("BEFORE CLAMP end x: %d, end y: %d\n", end.x, end.y);
    end.x = clamp(0, end.x, width);
    end.y = clamp(0, end.y, height);
    vel = (pos_t){end.x - des->_x, end.y -des->_y};
    printf("end x: %d, end y: %d\n", end.x, end.y);
    return get_broadcast_angle(&vel, des);
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
