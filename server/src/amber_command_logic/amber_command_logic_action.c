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

void amber_logic_eject(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_client_t *tmp = NULL;
    linked_list_t *clients = serv->_clients->nodes;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_id == client->_id)
            continue;
        if (tmp->_x != client->_x || tmp->_y != client->_y)
            continue;
        if (tmp->_direction == UP)
            tmp->_y = tmp->_y - 1 < 0 ? world->_height - 1 : tmp->_y - 1;
        if (tmp->_direction == DOWN)
            tmp->_y = tmp->_y + 1 >= world->_height ? 0 : tmp->_y + 1;
        if (tmp->_direction == RIGHT)
            tmp->_x = tmp->_x + 1 >= world->_width ? 0 : tmp->_x + 1;
        if (tmp->_direction == LEFT)
            tmp->_x = tmp->_x - 1 < 0 ? world->_width - 1 : tmp->_x - 1;
        int dir =  concave[tmp->_direction - 1][(client->_direction - 1) * 2];
        printf("push %d\n", tmp->_direction);
        printf("invert push %d\n", invert(tmp->_direction));
        printf("LA DIRECXTION MACHIN BIDULE: %d\n", dir);
    }
}
