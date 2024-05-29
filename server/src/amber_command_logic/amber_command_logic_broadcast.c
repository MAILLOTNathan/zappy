/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_broadcast
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

static int get_direction_message(amber_client_t *src, amber_client_t *des,
    int width, int height)
{
    int distances[2] = {get_distance(src->_x, des->_x, width),
        get_distance(src->_y, des->_y, height)};
    int directions[2] = {get_direction_action(src->_x, des->_x, width),
        get_direction_action(src->_y, des->_y, height)};
    bool *perimeter = NULL;

    printf("Player position:\n\tx = %d\n\ty = %d\n", src->_x, src->_y);
    printf("Enemy position:\n\tx = %d\n\ty = %d\n", des->_x, des->_y);
    printf("destination position:\n\tx = %d\n\ty = %d\n",
        distances[0] * directions[0], distances[1] * directions[1]);
    perimeter = initialize_perimeter(directions);
    perimeter = precise_perimeter(perimeter, distances);
    display_perimeter(perimeter);
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
        printf("%d\n", get_direction_message(client, tmp, world->_width,
            world->_height));
    }
}
