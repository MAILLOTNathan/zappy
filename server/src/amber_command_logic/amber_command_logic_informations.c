/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_informations
*/

#include "amber_logic.h"

void amber_look_vertical(amber_client_t *client, amber_world_t *world)
{
    int start_y = clamp(0, client->_y - client->_level, world->_height);
    int start_x = clamp(0, client->_x + client->_level, world->_width);
    int offset = 0;

    for (int i = client->_level; i > 0; i--) {
        for (int j = i; )
    }
}

void amber_logic_look(amber_client_t *client, amber_world_t *world)
{
    char **array = string_to_string_array("[ ]");

    for (int i = 0; i < client->_level; i++) {
        array = insert_array(array, )
        for (int j = 0; j < i; j++) {

        }
    }
}

void amber_logic_inventory(amber_client_t *client, amber_world_t *world)
{
    box_t *inv = client->_inventory;

    dprintf(INVENTORY, inv->_food, inv->_linemate, inv->_deraumere,
    inv->_sibur, inv->_mendiane, inv->_phiras, inv->_thystame);
}

void amber_logic_connect_br(amber_client_t *client, amber_world_t *world)
{
    
}
