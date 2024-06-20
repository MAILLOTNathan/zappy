/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_action
*/

#include "amber_logic.h"
#include "amber_command_graphical.h"

const int concave[4][8] = {
    {1, 2, 3, 4, 5, 6, 7, 8},
    {3, 4, 5, 6, 7, 8, 1, 2},
    {5, 6, 7, 8, 1, 2, 3, 4},
    {7, 8, 1, 2, 3, 4, 5, 6}
};

static direction_t invert(direction_t d)
{
    switch (d) {
        case UP:
            return DOWN;
        case DOWN:
            return UP;
        case RIGHT:
            return LEFT;
        case LEFT:
            return RIGHT;
        default:
            return 0;
    }
}

static void update_client_pos(direction_t dir, amber_trantor_t *tran,
    amber_world_t *world)
{
    world->_case[tran->_y][tran->_x]._players--;
    if (dir == UP)
        tran->_y = tran->_y - 1 < 0 ? world->_height - 1 : tran->_y - 1;
    if (dir == DOWN)
        tran->_y = tran->_y + 1 >= world->_height ? 0 : tran->_y + 1;
    if (dir == RIGHT)
        tran->_x = tran->_x + 1 >= world->_width ? 0 : tran->_x + 1;
    if (dir == LEFT)
        tran->_x = tran->_x - 1 < 0 ? world->_width - 1 : tran->_x - 1;
    world->_case[tran->_y][tran->_x]._players++;
}

static void manage_eject_send(amber_net_cli_t *client, amber_net_cli_t *tmp,
    amber_world_t *world, amber_serv_t *serv)
{
    int dir = 0;
    amber_trantor_t *trantor = TRANTOR(client);
    amber_trantor_t *t_trant = TRANTOR(tmp);

    update_client_pos(trantor->_direction, t_trant, world);
    if (trantor->_direction == UP || trantor->_direction == DOWN) {
        dir = concave[t_trant->_direction - 1]
        [(invert(trantor->_direction) - 1)* 2];
    } else
        dir = concave[t_trant->_direction - 1][(trantor->_direction - 1) * 2];
    snprintfizer(tmp, "eject: %d", dir);
    amber_event_pex(tmp, serv->_graphic_clients);
}

void amber_logic_eject(amber_net_cli_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_net_cli_t *tmp = NULL;
    amber_trantor_t *t_trant = NULL;
    amber_trantor_t *trantor = TRANTOR(client);
    linked_list_t *clients = serv->_clients->nodes;
    bool is_eject = false;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_net_cli_t *)node->data;
        t_trant = TRANTOR(tmp);
        if (tmp->_id == client->_id)
            continue;
        if (t_trant->_x != trantor->_x || t_trant->_y != trantor->_y)
            continue;
        is_eject = true;
        manage_eject_send(client, tmp, world, serv);
    }
    if (is_eject)
        return send_cli_msg(client, "ok");
    return send_cli_msg(client, "ko 9");
}

void amber_logic_fork(amber_net_cli_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_trantor_t *trantor = TRANTOR(client);

    amber_event_pfk(client, serv);
    push_back_list(world->_eggs, world, trantor->_x, trantor->_y,
        trantor->_team_name, world->_last_egg_id);
    amber_event_enw(client, serv->_graphic_clients, world->_last_egg_id);
    world->_last_egg_id++;
    send_cli_msg(client, "ok");
}
