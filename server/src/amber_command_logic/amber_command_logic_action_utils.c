/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_action_utils
*/

#include "amber_logic.h"

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
