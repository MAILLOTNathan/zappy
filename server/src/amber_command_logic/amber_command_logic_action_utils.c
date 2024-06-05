/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_action_utils
*/

#include "amber_logic.h"

const int conversions[][8] = {
    {2, 1, 8, 7, 6, 5, 4, 3},
    {6, 5, 4, 3, 2, 1, 8, 7},
    {4, 3, 2, 1, 8, 7, 6, 5},
    {8, 7, 6, 5, 4, 3, 2, 1},
    {0}
};

static bool *precise_center(bool *perim, int *distances)
{
    if (ABS(distances[0]) == 0 || ABS(distances[1]) == 0) {
            perim[0] = false;
            perim[2] = false;
            perim[4] = false;
            perim[6] = false;
        if (ABS(distances[1]) == 0) {
            perim[1] = false;
            perim[5] = false;
        } else {
            perim[3] = false;
            perim[7] = false;
        }
    }
    return perim;
}

bool *precise_perimeter(bool *perim, int *distances)
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
    return precise_center(perim, distances);
}

int get_distance(int src, int dest, int max)
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

int get_direction_action(int src, int dest, int max)
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

bool *initialize_perimeter(int *directions)
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
