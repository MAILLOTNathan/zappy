/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_action
*/

#include "amber_logic.h"

static int get_distance(int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

static int update_pos(int *pos, int dis_ref, int x2, int y2)
{
    int dis_new = get_distance(pos[0], pos[1], x2, y2);

    if (dis_new < dis_ref) {
        pos[0] = x2;
        pos[1] = y2;
        return dis_new;
    }
    return dis_ref;
}

static int get_direction_message(amber_client_t *src, amber_client_t *des,
    int width, UNUSED int height)
{
    int x = des->_x - src->_x;
    int y = des->_y - src->_y;
    int *pos = calloc(2, sizeof(int));
    int dis_ref = x * x + y * y;

    if (x == 0 && y == 0)
        return 0;
    pos[0] = des->_x;
    pos[1] = des->_y;
    dis_ref = update_pos(pos, dis_ref, des->_x - width, des->_y);
    printf("FIRST\n");
    printf("SRC: %d %d\n", src->_x, src->_y);
    printf("DES: %d %d\n", des->_x, des->_y);
    printf("pos[0] = %d, pos[1] = %d\n", pos[0], pos[1]);
    printf("dis_ref = %d\n", dis_ref);
    dis_ref = update_pos(pos, dis_ref, des->_x + width, des->_y);
    printf("SECOND\n");
    printf("SRC: %d %d\n", src->_x, src->_y);
    printf("DES: %d %d\n", des->_x, des->_y);
    printf("pos[0] = %d, pos[1] = %d\n", pos[0], pos[1]);
    printf("dis_ref = %d\n", dis_ref);
    dis_ref = update_pos(pos, dis_ref, des->_x, des->_y - height);
    printf("THIRD\n");
    printf("SRC: %d %d\n", src->_x, src->_y);
    printf("DES: %d %d\n", des->_x, des->_y);
    printf("pos[0] = %d, pos[1] = %d\n", pos[0], pos[1]);
    printf("dis_ref = %d\n", dis_ref);
    dis_ref = update_pos(pos, dis_ref, des->_x, des->_y + height);
    printf("FOURTH\n");
    printf("SRC: %d %d\n", src->_x, src->_y);
    printf("DES: %d %d\n", des->_x, des->_y);
    printf("pos[0] = %d, pos[1] = %d\n", pos[0], pos[1]);
    printf("dis_ref = %d\n", dis_ref);
    dis_ref = update_pos(pos, dis_ref, des->_x - width, des->_y - height);
    printf("FIFTH\n");
    printf("SRC: %d %d\n", src->_x, src->_y);
    printf("DES: %d %d\n", des->_x, des->_y);
    printf("pos[0] = %d, pos[1] = %d\n", pos[0], pos[1]);
    printf("dis_ref = %d\n", dis_ref);
    dis_ref = update_pos(pos, dis_ref, des->_x + width, des->_y + height);
    printf("SIXTH\n");
    printf("SRC: %d %d\n", src->_x, src->_y);
    printf("DES: %d %d\n", des->_x, des->_y);
    printf("pos[0] = %d, pos[1] = %d\n", pos[0], pos[1]);
    printf("dis_ref = %d\n", dis_ref);
    dis_ref = update_pos(pos, dis_ref, des->_x - width, des->_y + height);
    printf("SEVENTH\n");
    printf("SRC: %d %d\n", src->_x, src->_y);
    printf("DES: %d %d\n", des->_x, des->_y);
    printf("pos[0] = %d, pos[1] = %d\n", pos[0], pos[1]);
    printf("dis_ref = %d\n", dis_ref);
    dis_ref = update_pos(pos, dis_ref, des->_x + width, des->_y - height);
    printf("EIGHTH\n");
    printf("SRC: %d %d\n", src->_x, src->_y);
    printf("DES: %d %d\n", des->_x, des->_y);
    printf("pos[0] = %d, pos[1] = %d\n", pos[0], pos[1]);
    printf("dis_ref = %d\n", dis_ref);
    return 0;
}

void amber_logic_broadcast(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_client_t *tmp = NULL;
    linked_list_t *clients = serv->_clients->nodes;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        printf("%d\n", get_direction_message(client, tmp, world->_width,
            world->_height));
    }
}
