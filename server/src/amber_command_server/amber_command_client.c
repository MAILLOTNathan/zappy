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
            ((amber_net_cli_t *)client_graphical->data)->_id);
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

static void content_display(int fd, amber_trantor_t *trantor)
{
    dprintf(fd, "================USER AI================\n");
    dprintf(fd, INFO_CLIENT,
        trantor->_id, trantor->_team_name, trantor->_y,
        trantor->_x, trantor->_level);
    dprintf(fd, "Direction: %s\n",
        get_direction(trantor->_direction));
    dprintf(fd, INVENTORY, trantor->_inventory->_food,
        trantor->_inventory->_linemate, trantor->_inventory->_deraumere,
        trantor->_inventory->_sibur, trantor->_inventory->_mendiane,
        trantor->_inventory->_phiras, trantor->_inventory->_thystame);
    dprintf(fd, "========================================\n");
}

void amber_serv_clients(amber_serv_t *serv, UNUSED amber_world_t *world,
    UNUSED char **cmd)
{
    linked_list_t *tmp = serv->_clients->nodes;
    amber_net_cli_t *client = NULL;

    for (; tmp; tmp = tmp->next) {
        client = (amber_net_cli_t *)tmp->data;
        if (client->_type != AI)
            continue;
        content_display(FDDEBUG(serv), TRANTOR(client));
    }
    display_client_graphic(FDDEBUG(serv), serv->_graphic_clients->nodes);
}
