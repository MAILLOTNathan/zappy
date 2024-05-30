/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_action
*/

#include "amber_logic.h"

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

static void update_client_pos(direction_t dir, amber_client_t *client,
    amber_world_t *world)
{
    if (dir == UP)
        client->_y = client->_y - 1 < 0 ? world->_height - 1 : client->_y - 1;
    if (dir == DOWN)
        client->_y = client->_y + 1 >= world->_height ? 0 : client->_y + 1;
    if (dir == RIGHT)
        client->_x = client->_x + 1 >= world->_width ? 0 : client->_x + 1;
    if (dir == LEFT)
        client->_x = client->_x - 1 < 0 ? world->_width - 1 : client->_x - 1;
}

void amber_logic_eject(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_client_t *tmp = NULL;
    linked_list_t *clients = serv->_clients->nodes;
    int dir = 0;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_id == client->_id)
            continue;
        if (tmp->_x != client->_x || tmp->_y != client->_y)
            continue;
        update_client_pos(client->_direction, tmp, world);
        if (client->_direction == UP || client->_direction == DOWN) {
            dir = concave[tmp->_direction - 1]
            [(invert(client->_direction) - 1)* 2];
        } else
            dir = concave[tmp->_direction - 1][(client->_direction - 1) * 2];
        dprintf(tmp->_tcp._fd, "eject: %d\n", dir);
    }
}

void amber_logic_fork(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    push_back_list(world->_eggs, world, client->_x, client->_y,
        client->_team_name, world->_last_egg_id);
    world->_last_egg_id++;
    dprintf(client->_tcp._fd, "ok\n");
}