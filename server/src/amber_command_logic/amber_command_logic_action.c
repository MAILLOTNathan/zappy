/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_action
*/

#include "amber_logic.h"
static void display_perimeter(bool *perimeter)
{
    printf("Perimeter:\n");
    printf("%s ", perimeter[0] ? "X" : "O");
    printf("%s ", perimeter[1] ? "X" : "O");
    printf("%s\n", perimeter[2] ? "X" : "O");
    printf("%s P ", perimeter[7] ? "X" : "O");
    printf("%s\n", perimeter[3] ? "X" : "O");
    printf("%s ", perimeter[6] ? "X" : "O");
    printf("%s ", perimeter[5] ? "X" : "O");
    printf("%s\n", perimeter[4] ? "X" : "O");
}

static int get_direction_by_pos(amber_client_t *src, int x, int y)
{
    int distances[2] = {get_distance(src->_x, x, 10),
        get_distance(src->_y, y, 10)};
    int directions[2] = {get_direction_action(src->_x, x, 10),
        get_direction_action(src->_y, y, 10)};
    bool *perimeter = NULL;

    perimeter = initialize_perimeter(directions);
    perimeter = precise_perimeter(perimeter, distances);
    display_perimeter(perimeter);
    return get_direction_by_perimeter(perimeter, src);
}

void amber_logic_eject(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_client_t *tmp = NULL;
    linked_list_t *clients = serv->_clients->nodes;
    int x = 0;
    int y = 0;

    (void) world;
    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_id == client->_id)
            continue;
        if (tmp->_x != client->_x || tmp->_y != client->_y)
            continue;
        x = tmp->_x;
        y = tmp->_y;
        printf("%d\n", get_direction_by_pos(tmp, x, y));
    }
}
