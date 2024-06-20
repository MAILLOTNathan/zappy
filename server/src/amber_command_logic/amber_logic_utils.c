/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_logic_utils
*/

#include "amber_logic.h"
#include "amber_command_graphical.h"
#include <signal.h>

static void handle_sigpipe(int sig)
{
    (void)sig;
    return;
}

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

void send_cli_msg(amber_net_cli_t *client, const char *message)
{
    signal(SIGPIPE, handle_sigpipe);
    dprintf(client->_tcp._fd, "%s\n", message);
    signal(SIGPIPE, SIG_DFL);
}

static void drop_item(amber_world_t *world, int x, int y, box_t *inv)
{
    if (inv->_food > 0) {
        world->_case[y][x]._food += inv->_food;
        world->_food_info._c_value += inv->_food;
    }
    world->_case[y][x]._linemate += inv->_linemate;
    world->_case[y][x]._deraumere += inv->_deraumere;
    world->_case[y][x]._sibur += inv->_sibur;
    world->_case[y][x]._mendiane += inv->_mendiane;
    world->_case[y][x]._phiras += inv->_phiras;
    world->_case[y][x]._thystame += inv->_thystame;
    world->_linemate_info._c_value += inv->_linemate;
    world->_deraumere_info._c_value += inv->_deraumere;
    world->_sibur_info._c_value += inv->_sibur;
    world->_mendiane_info._c_value += inv->_mendiane;
    world->_phiras_info._c_value += inv->_phiras;
    world->_thystame_info._c_value += inv->_thystame;
}

static void check_clock_food(amber_net_cli_t *client, amber_world_t *world,
    linked_list_t *node, amber_serv_t *server)
{
    amber_trantor_t *trantor = TRANTOR(client);

    if (trantor->_clock_food >= get_time_in_microseconds())
        return;
    trantor->_inventory->_food--;
    if (trantor->_inventory->_food < 0) {
        drop_item(world, trantor->_x, trantor->_y, trantor->_inventory);
        world->_case[trantor->_y][trantor->_x]._players--;
        printf("[AMBER INFO] Client %d died\n", client->_tcp._fd);
        amber_event_pdi(client, server->_graphic_clients);
        snprintfizer(client, "dead");
        amber_event_pdi(client, server->_graphic_clients);
        remove_node(&server->_clients, node, true);
    } else {
        trantor->_clock_food = get_new_time_in_microseconds(126 / world->_freq);
    }
}

void amber_check_client_alive(amber_serv_t *server, amber_world_t *world)
{
    linked_list_t *node = server->_clients->nodes;
    linked_list_t *ref = server->_clients->nodes;
    int len = list_len(server->_clients);
    amber_net_cli_t *client = NULL;
    amber_trantor_t *trantor = NULL;

    for (int i = 0; i < len; i++) {
        client = CAST(amber_net_cli_t *, node->data);
        trantor = TRANTOR(client);
        ref = node->next;
        if (trantor->_is_incantating || trantor->_team_name == NULL) {
            node = ref;
            continue;
        }
        check_clock_food(client, world, node, server);
        node = ref;
    }
}
