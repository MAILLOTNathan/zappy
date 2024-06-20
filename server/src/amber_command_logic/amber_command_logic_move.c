/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_move
*/

#include "amber_logic.h"
#include "amber_command_graphical.h"

static void update_pos_trantor(amber_trantor_t *trantor, amber_world_t *world)
{
    trantor->_x = world->_width == trantor->_x ? 0 : trantor->_x;
    trantor->_y = world->_height == trantor->_y ? 0 : trantor->_y;
    world->_case[trantor->_y][trantor->_x]._players++;
}

void amber_logic_forward(amber_net_cli_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_trantor_t *trantor = TRANTOR(client);

    world->_case[trantor->_y][trantor->_x]._players--;
    switch (trantor->_direction) {
        case UP:
            trantor->_y = clamp(0, trantor->_y - 1, world->_height);
            break;
        case DOWN:
            trantor->_y = clamp(0, trantor->_y + 1,
            world->_height);
            break;
        case LEFT:
            trantor->_x = clamp(0, trantor->_x - 1, world->_width);
            break;
        case RIGHT:
            trantor->_x = clamp(0, trantor->_x + 1, world->_width);
    }
    send_cli_msg(client, "ok");
    update_pos_trantor(trantor, world);
    amber_event_idmoved(client, serv->_graphic_clients, 'F');
}

void amber_logic_right(amber_net_cli_t *client, UNUSED amber_world_t *world,
    amber_serv_t *serv)
{
    switch (TRANTOR(client)->_direction) {
        case UP:
            TRANTOR(client)->_direction = RIGHT;
            break;
        case DOWN:
            TRANTOR(client)->_direction = LEFT;
            break;
        case LEFT:
            TRANTOR(client)->_direction = UP;
            break;
        case RIGHT:
            TRANTOR(client)->_direction = DOWN;
            break;
        default:
            break;
    }
    send_cli_msg(client, "ok");
    amber_event_idmoved(client, serv->_graphic_clients, 'R');
}

void amber_logic_left(amber_net_cli_t *client, UNUSED amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    switch (TRANTOR(client)->_direction) {
        case UP:
            TRANTOR(client)->_direction = LEFT;
            break;
        case DOWN:
            TRANTOR(client)->_direction = RIGHT;
            break;
        case LEFT:
            TRANTOR(client)->_direction = DOWN;
            break;
        case RIGHT:
            TRANTOR(client)->_direction = UP;
            break;
        default:
            break;
    }
    send_cli_msg(client, "ok");
    amber_event_idmoved(client, serv->_graphic_clients, 'L');
}
