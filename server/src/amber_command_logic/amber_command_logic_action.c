/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_action
*/

#include "amber_logic.h"

const int conversions[][8] = {
    {2, 1, 8, 7, 6, 5, 4, 3},
    {6, 5, 4, 3, 2, 1, 8, 7},
    {4, 3, 2, 1, 8, 7, 6, 5},
    {8, 7, 6, 5, 4, 3, 2, 1},
    {0}
};

static int get_distance(int src, int dest, int max)
{
    if (dest > src) {
        if (abs(dest - src) < abs((max - dest) + src))
            return dest - src;
        return (max - dest) + src;
    }
    if (dest < src) {
        if (abs(src - dest) < abs((max - src) + dest))
            return src - dest;
        return (max - src) + dest;
    }
    return 0;
}

static int get_direction(int src, int dest, int max)
{
    if (dest > src) {
        if (abs(dest - src) < abs((max - dest) + src))
            return 1;
        return -1;
    }
    if (dest < src) {
        if (abs(src - dest) < abs((max - src) + dest))
            return -1;
        return 1;
    }
    return 0;
}

static bool *initialize_perimeter(int *directions)
{
    bool *perim = malloc(sizeof(bool) * 8);

    if (!perim)
        return NULL;
    perim[0] = directions[0] == -1 || directions[1] == -1;
    perim[1] = directions[0] == 0 || directions[1] == -1;
    perim[2] = directions[0] == 1 || directions[1] == -1;
    perim[3] = directions[0] == 1 || directions[1] == 0;
    perim[4] = directions[0] == 1 || directions[1] == 1;
    perim[5] = directions[0] == 0 || directions[1] == 1;
    perim[6] = directions[0] == -1 || directions[1] == 1;
    perim[7] = directions[0] == -1 || directions[1] == 0;
    perim[0] = directions[0] == 1 || directions[1] == 1 ? false : perim[0];
    perim[2] = directions[0] == -1 || directions[1] == 1 ? false : perim[2];
    perim[4] = directions[0] == -1 || directions[1] == -1 ? false : perim[4];
    perim[6] = directions[0] == 1 || directions[1] == -1 ? false : perim[6];
    return perim;
}

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

static bool *precise_perimeter(bool *perim, int *distances)
{
    if (ABS(distances[0]) > ABS(distances[1])) {
        if (ABS(distances[0]) > 1) {
            perim[1] = false;
            perim[5] = false;
        }
    }
    if (ABS(distances[1]) > ABS(distances[0]))
        if (ABS(distances[1]) > 1) {
            perim[3] = false;
            perim[7] = false;
        }
    return perim;
}

int get_direction_by_perimeter(bool *perimeter, amber_client_t *client)
{
    int index = 0;

    for (index = 0; perimeter[index] == true; index++);
    switch (client->_direction) {
        case UP:
            return conversions[0][index];
        case DOWN:
            return conversions[1][index];
        case RIGHT:
            return conversions[2][index];
        case LEFT:
            return conversions[3][index];
        default:
            break;
    }
    return 0;
}

static int get_direction_message(amber_client_t *src, amber_client_t *des,
    int width, int height)
{
    int distances[2] = {get_distance(src->_x, des->_x, width),
        get_distance(src->_y, des->_y, height)};
    int directions[2] = {get_direction(src->_x, des->_x, width),
        get_direction(src->_y, des->_y, height)};
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
