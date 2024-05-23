/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_informations
*/

#include "amber_logic.h"

static void amber_look_up(amber_client_t *client, amber_world_t *world)
{
    int level = client->_level;
    int start_y = clamp(0, client->_y - level, world->_height);
    int start_x = clamp(0, client->_x + level, world->_width);
    int offset = 0;
    int x = 0;
    int y = 0;

    for (int i = level; i > 0; i--) {
        y = clamp(0, start_y + offset, world->_height);
        y = y == world->_height ? 0 : y;
        for (int j = 0; i * 2 + 1 > j; j++) {
            x = clamp(0, start_x - j, world->_width);
            printf("x: %d, y: %d\n", x, y);
        }
        offset++;
    }
}

static void amber_look_left(amber_client_t *client, amber_world_t *world)
{
    int level = client->_level;
    int start_y = clamp(0, client->_y - level, world->_height);
    int start_x = clamp(0, client->_x - level, world->_width);
    int offset = 0;
    int x = 0;
    int y = 0;

    for (int i = level; i > 0; i--) {
        x = clamp(0, start_x + offset, world->_width);
        x = x == world->_width ? 0 : x;
        for (int j = 0; i * 2 + 1 > j; j++) {
            y = clamp(0, start_y + j, world->_height);
            y = y == world->_height ? 0 : y;
            printf("x: %d, y: %d\n", x, y);
        }
        offset++;
    }
}

static void amber_look_down(amber_client_t *client, amber_world_t *world)
{
    int level = client->_level;
    int start_y = clamp(0, client->_y + level, world->_height);
    int start_x = clamp(0, client->_x - level, world->_width);
    int offset = 0;
    int x = 0;
    int y = 0;

    for (int i = level; i > 0; i--) {
        y = clamp(0, start_y - offset, world->_height);
        y = y == world->_height ? 0 : y;
        for (int j = 0; i * 2 + 1 > j; j++) {
            x = clamp(0, start_x + j, world->_width);
            x = x == world->_width ? 0 : x;
            printf("x: %d, y: %d\n", x, y);
        }
        offset++;
    }
}

static void amber_look_right(amber_client_t *client, amber_world_t *world)
{
    int level = client->_level;
    int start_y = clamp(0, client->_y - level, world->_height);
    int start_x = clamp(0, client->_x + level, world->_width);
    printf("start_x: %d, start_y: %d\n", start_x, start_y);
    int offset = 0;
    int x = 0;
    int y = 0;

    for (int i = level; i > 0; i--) {
        x = clamp(0, start_x - offset, world->_width);
        x = x == world->_width ? 0 : x;
        for (int j = 0; i * 2 + 1 > j; j++) {
            y = clamp(0, start_y + j, world->_height);
            y = y == world->_height ? 0 : y;
            printf("x: %d, y: %d\n", x, y);
        }
        offset++;
    }
}

void amber_logic_look(amber_client_t *client, amber_world_t *world)
{
    // char **array = string_to_string_array("[ ]");

    switch (client->_direction)
    {
    case UP:
        amber_look_up(client, world);
        break;
    case LEFT:
        amber_look_left(client, world);
        break;
    case DOWN:
        amber_look_down(client, world);
        break;
    case RIGHT:
        amber_look_right(client, world);
    }
}

void amber_logic_inventory(amber_client_t *client, UNUSED amber_world_t *world)
{
    box_t *inv = client->_inventory;

    dprintf(client->_tcp._fd, INVENTORY, inv->_food, inv->_linemate,
    inv->_deraumere, inv->_sibur, inv->_mendiane,
    inv->_phiras, inv->_thystame);
}

// void amber_logic_connect_br(amber_client_t *client, amber_world_t *world)
// {

// }
