/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_client_utils
*/

#include "amber_manage_client.h"
#include "amber_command_graphical.h"
#include "amber_logic.h"

amber_client_t *amber_init_client_by_egg(amber_client_t *client, egg_t *egg,
    double freq)
{
    client->_is_graphical = false;
    client->_team_name = strdup(egg->_team);
    client->_direction = egg->_direction;
    client->_x = egg->_x;
    client->_y = egg->_y;
    client->_level = 1;
    client->_id = egg->_id;
    client->_inventory = amber_world_case_init();
    client->_inventory->_food = 10;
    client->_is_incantating = false;
    client->_clock_food = get_new_time_in_microseconds(126 / freq);
    amber_destroy_egg(egg);
    return client;
}

static char get_direction(direction_t direction)
{
    switch (direction) {
    case UP:
        return 'N';
    case DOWN:
        return 'S';
    case LEFT:
        return 'W';
    case RIGHT:
        return 'E';
    }
    return 'N';
}

static void send_graphical_players(amber_client_t *gra, list_t *client_ai)
{
    linked_list_t *tmp = client_ai->nodes;
    amber_client_t *client = NULL;

    for (; tmp; tmp = tmp->next) {
        client = (amber_client_t *)tmp->data;
        if (client->_team_name == NULL)
            continue;
        dprintf(gra->_tcp._fd, "pnw %d %d %d %c %d %s\n", client->_id,
        client->_x, client->_y, get_direction(client->_direction),
        client->_level, client->_team_name);
    }
}

static bool check_different_mode(amber_client_t *client, amber_serv_t *serv,
    char **arg)
{
    if (length_string_array(arg) != 1)
        return false;
    if (strcmp(arg[0], "GRAPHIC") == 0) {
        push_back_list(serv->_graphic_clients, client->_tcp._fd, true);
        send_graphical_players(client, serv->_clients);
        remove_node(&serv->_clients, list_find_node_p(serv->_clients, client),
        false);
        printf("[AMBER INFO] New graphical client connected\n");
        return false;
    }
    if (strcmp(arg[0], "DEBUG") == 0 && serv->_debug_client._fd != 1) {
        serv->_debug_client._fd = client->_tcp._fd;
        remove_node(&serv->_clients, list_find_node_p(serv->_clients, client),
        false);
        printf("[AMBER INFO] New debug client connected\n");
        return false;
    }
    return true;
}

static bool check_if_enough_places(amber_serv_t *serv, char *team,
    int client_nb, amber_client_t *client)
{
    if (amber_get_nbr_clients_by_team(serv, team) >= client_nb) {
        printf("[AMBER ERROR] Too many clients for team %s\n", team);
        send_cli_msg(client, "ko\n");
        return false;
    }
    printf("[AMBER INFO] New ai connected\n");
    return true;
}

bool amber_init_client(amber_client_t *client, amber_serv_t *serv,
    amber_world_t *world, char **arg)
{
    egg_t *egg = NULL;

    if (!check_different_mode(client, serv, arg))
        return false;
    egg = amber_get_egg_by_team(world, arg[0]);
    if (!egg) {
        printf("[AMBER ERROR] No egg available for team %s\n", arg[0]);
        dprintf(client->_tcp._fd, "ko\n");
        remove_node(&serv->_clients, list_find_node_p(serv->_clients, client),
        true);
        return false;
    }
    if (!check_if_enough_places(serv, arg[0], world->_clientsNb, client))
        return false;
    client = amber_init_client_by_egg(client, egg, world->_freq);
    dprintf(client->_tcp._fd, "%d\n", world->_clientsNb -
    amber_get_nbr_clients_by_team(serv, arg[0]));
    dprintf(client->_tcp._fd, "%d %d\n", world->_width, world->_height);
    amber_event_pnw(client, serv->_graphic_clients);
    return true;
}
