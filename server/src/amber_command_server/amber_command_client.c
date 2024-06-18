/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_client
*/

#include "amber_command_server.h"
#include "amber_logic.h"

static void display_client_graphic(int fd, linked_list_t *client_graphical)
{
    while (client_graphical) {
        dprintf(fd, "================USER GRAPHIC================\n");
        dprintf(fd, "Client ID: %d\n",
            ((amber_client_t *)client_graphical->data)->_id);
        dprintf(fd, "========================================\n");
        client_graphical = client_graphical->next;
    }
}

static char *get_direction(int direction)
{
    if (direction == UP)
        return "UP";
    if (direction == RIGHT)
        return "RIGHT";
    if (direction == DOWN)
        return "DOWN";
    if (direction == LEFT)
        return "LEFT";
    return "UNKNOWN";
}

void amber_serv_clients(amber_serv_t *serv, UNUSED amber_world_t *world,
    UNUSED char **cmd)
{
    linked_list_t *tmp = serv->_clients->nodes;
    amber_client_t *client = NULL;

    for (; tmp; tmp = tmp->next) {
        client = (amber_client_t *)tmp->data;
        if (client->_team_name == NULL)
            continue;
        dprintf(FDDEBUG(serv), "================USER AI================\n");
        dprintf(FDDEBUG(serv), INFO_CLIENT,
            client->_id, client->_team_name, client->_y,
            client->_x, client->_level);
        dprintf(FDDEBUG(serv), "Direction: %s\n",
        get_direction(client->_direction));
        dprintf(FDDEBUG(serv), INVENTORY, client->_inventory->_food,
            client->_inventory->_linemate, client->_inventory->_deraumere,
            client->_inventory->_sibur, client->_inventory->_mendiane,
            client->_inventory->_phiras, client->_inventory->_thystame);
        dprintf(FDDEBUG(serv), "========================================\n");
    }
    display_client_graphic(FDDEBUG(serv), serv->_graphic_clients->nodes);
}
