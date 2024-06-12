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

static bool check_inside_range(int x, int y, pos_t *des)
{
    int offset = -1;
    int tmp = 0;

    for (int i = 0; i < 3; i++) {
        tmp = (des->y + offset);
        if (y == tmp && x == (des->x - 1))
            return true;
        if (y == tmp && x == (des->x))
            return true;
        if (y == tmp && x == (des->x + 1))
            return true;
        offset += 1;
    }
    return false;
}

static int get_ratio(float *dy, float *yi, float dx)
{
    if (*dy < 0) {
        *yi = -1;
        *dy *= -1;
    }
    return (2 * (*dy)) - dx;
}

static pos_t line_low(pos_t *m, pos_t *m2, bool inverted)
{
    float dx = m2->x - m->x;
    float dy = m2->y - m->y;
    float yi = 1;
    float y = m->y;
    int x = m->x;
    float D = get_ratio(&dy, &yi, dx);

    for (; !check_inside_range(x, y, m2); x++) {
        if (D > 0) {
            y = y + yi;
            D = D + (2 * (dy - dx));
        } else {
            D = D + 2 * dy;
        }
        printf("pos x = %i\npos y = %f\n", x, y);
        if (inverted && (y != m->y || x != m->x))
            break;
    }
    return (pos_t){x, y};
}

static pos_t line_high(pos_t *m, pos_t *m2, bool inverted)
{
    float dx = m2->x - m->x;
    float dy = m2->y - m->y;
    float xi = 1;
    float x = m->x;
    int y = m->y;
    float D = get_ratio(&dx, &xi, dy);

    for (; !check_inside_range(x, y, m2); y++) {
        if (D > 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        } else {
            D = D + 2 * dx;
        }
        printf("pos x = %f\npos y = %d\n", x, y);
        if (inverted && (y != m->y || x != m->x))
            break;
    }
    return (pos_t){x, y};
}

pos_t plotline(pos_t *m, pos_t *m2)
{
    if (m2->x == m->x && m2->y == m->y)
        return (pos_t){m->x, m->y};
    if (abs(m2->y - m->y) < abs(m2->x - m->x)) {
        if (m->x > m2->x) {
            printf("INVERT m2 and m\n");
            return line_low(m2, m, true);
        } else
            return line_low(m, m2, false);
    } else {
        if (m->y > m2->y) {
            printf("INVERT m2 and m\n");
            return line_high(m2, m, true);
        } else
            return line_high(m, m2, false);
    }
    return (pos_t){-1, -1};
}

int get_distance(int src, int dest, int max)
{
    int distance = dest - src;

    if (distance > max / 2)
        distance -= max;
    return distance;
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
