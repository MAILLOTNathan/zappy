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

static void check_clock_food(amber_client_t *client, amber_world_t *world,
    linked_list_t *node, amber_serv_t *server)
{
    if (client->_clock_food >= get_time_in_microseconds())
        return;
    client->_inventory->_food--;
    if (client->_inventory->_food < 0) {
        dprintf(client->_tcp._fd, "dead\n");
        remove_node(&server->_clients, node, true);
    } else
        world->_food_info._c_value--;
    client->_clock_food = get_new_time_in_microseconds(126 / world->_freq);
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
        if (client->_is_incantating || client->_team_name == NULL) {
            node = ref;
            continue;
        }
        check_clock_food(client, world, node, server);
        node = ref;
    }
}
