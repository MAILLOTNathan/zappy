/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_client
*/

#include "amber_command_server.h"
#include "amber_logic.h"

static void display_client_graphic(linked_list_t *client_graphical)
{
    while (client_graphical) {
        printf("================USER GRAPHIC================\n");
        printf("Client ID: %d\n",
            ((amber_client_t *)client_graphical->data)->_id);
        printf("========================================\n");
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

void amber_serv_clients(amber_serv_t *server, UNUSED amber_world_t *world,
    UNUSED char **cmd)
{
    linked_list_t *tmp = server->_clients->nodes;
    amber_client_t *client = NULL;

    printf("[AMBER COMMAND] /clients\n");
    while (tmp) {
        client = (amber_client_t *)tmp->data;
        printf("================USER AI================\n");
        printf("Client ID: %d | Team: %s | Position: y=%d x=%d | Level: %d | ",
            client->_id, client->_team_name, client->_y,
            client->_x, client->_level);
        printf("Direction: %s\n", get_direction(client->_direction));
        printf(INVENTORY, client->_inventory->_food,
            client->_inventory->_linemate, client->_inventory->_deraumere,
            client->_inventory->_sibur, client->_inventory->_mendiane,
            client->_inventory->_phiras, client->_inventory->_thystame);
        printf("========================================\n");
        tmp = tmp->next;
    }
    display_client_graphic(server->_graphic_clients->nodes);
}
