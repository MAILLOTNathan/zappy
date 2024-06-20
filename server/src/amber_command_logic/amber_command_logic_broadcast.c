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


int get_broadcast_angle(pos_t *vel, amber_trantor_t *des)
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

static int get_direction_message(amber_trantor_t *src, amber_trantor_t *des,
    int width, int height)
{
    pos_t distance = {get_distance(src->_x, des->_x, width),
        get_distance(src->_y, des->_y, height)};
    pos_t start_pos = {src->_x, src->_y};
    pos_t end_pos = {src->_x + distance.x, src->_y + distance.y};
    pos_t end = plotline(&start_pos, &end_pos);
    pos_t vel = {0, 0};

    if (end.x == 0 && des->_x == width - 1)
        end.x = width;
    if (end.y == 0 && des->_y == height - 1)
        end.y = height;
    vel = (pos_t){end.x - des->_x, end.y - des->_y};
    return get_broadcast_angle(&vel, des);
}

void amber_logic_broadcast(amber_net_cli_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_net_cli_t *tmp = NULL;
    linked_list_t *clients = serv->_clients->nodes;
    amber_trantor_t *trant = TRANTOR(client);
    amber_trantor_t *t_trant = NULL;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_net_cli_t *)node->data;
        t_trant = TRANTOR(tmp);
        if (tmp->_id == client->_id || t_trant->_team_name == NULL)
            continue;
        snprintfizer(tmp, "message %d, %s",
            get_direction_message(trant, t_trant, world->_width,
            world->_height), trant->_queue_command->_command->_arg);
    }
    amber_event_pbc(client, serv->_graphic_clients);
    send_cli_msg(client, "ok");
}
