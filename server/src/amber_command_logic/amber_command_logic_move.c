/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_move
*/

#include "amber_logic.h"

void amber_logic_forward(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    world->_case[client->_y][client->_x]._players--;
    switch (client->_direction) {
        case UP:
            client->_y = clamp(0, client->_y - 1, world->_height);
            break;
        case DOWN:
            client->_y = clamp(0, client->_y + 1,
            world->_height);
            break;
        case LEFT:
            client->_x = clamp(0, client->_x - 1, world->_width);
            break;
        case RIGHT:
            client->_x = clamp(0, client->_x + 1, world->_width);
    }
    client->_x = world->_width == client->_x ? 0 : client->_x;
    client->_y = world->_height == client->_y ? 0 : client->_y;
    world->_case[client->_y][client->_x]._players++;
    send_client_message(client, "ok");
}

void amber_logic_right(amber_client_t *client, UNUSED amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    switch (client->_direction) {
        case UP:
            client->_direction = RIGHT;
            break;
        case DOWN:
            client->_direction = LEFT;
            break;
        case LEFT:
            client->_direction = UP;
            break;
        case RIGHT:
            client->_direction = DOWN;
            break;
        default:
            break;
    }
    send_client_message(client, "ok");
}

void amber_logic_left(amber_client_t *client, UNUSED amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    switch (client->_direction) {
        case UP:
            client->_direction = LEFT;
            break;
        case DOWN:
            client->_direction = RIGHT;
            break;
        case LEFT:
            client->_direction = DOWN;
            break;
        case RIGHT:
            client->_direction = UP;
            break;
        default:
            break;
    }
    send_client_message(client, "ok");
}
