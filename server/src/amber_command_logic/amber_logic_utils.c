/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_logic_utils
*/

#include "amber_logic.h"

int clamp(int min, int current, int max)
{
    while (current < min || current > max) {
        if (current < min)
            current = max - (ABS(current) - ABS(min));
        if (current > max)
            current = min + (ABS(current) - max);
    }
    return current;
}

int real_clamp(int min, int current, int max)
{
    if (current < min)
        return min;
    if (current > max)
        return max;
    return current;
}

void send_client_message(amber_client_t *client, const char *message)
{
    dprintf(client->_tcp._fd, "%s\n", message);
}

void amber_check_client_alive(amber_serv_t *server, amber_world_t *world)
{
    linked_list_t *node = server->_clients->nodes;
    linked_list_t *ref = server->_clients->nodes;
    int len = list_len(server->_clients);
    amber_client_t *client = NULL;

    for (int i = 0; i < len; i++) {
        client = CAST(amber_client_t *, node->data);
        ref = node->next;
        client->_inventory->_food--;
        if (client->_inventory->_food < 0) {
            dprintf(client->_tcp._fd, "dead\n");
            remove_node(&server->_clients, node, true);
        } else {
            world->_food_info._c_value--;
        }
        node = ref;
    }
}
