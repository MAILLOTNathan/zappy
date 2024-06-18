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
        dprintf(gra->_tcp._fd, "pnw #%d %d %d %c %d %s\n", client->_id,
        client->_x, client->_y, get_direction(client->_direction),
        client->_level, client->_team_name);
    }
}

static bool check_different_mode(amber_client_t *client, amber_serv_t *serv,
    char **arg, amber_world_t *world)
{
    if (length_string_array(arg) != 1)
        return false;
    if (strncmp(arg[0], "GRAPHIC", 8) == 0) {
        push_back_list(serv->_graphic_clients, client->_tcp._fd, true);
        amber_send_egg_on_connection(client, world->_eggs);
        send_graphical_players(client, serv->_clients);
        remove_node(&serv->_clients, list_find_node_p(serv->_clients, client),
        false);
        printf("[AMBER INFO] New graphical client connected\n");
        return false;
    }
    if (strncmp(arg[0], "DEBUG", 5) == 0 && serv->_debug_client._fd != 1) {
        serv->_debug_client._fd = client->_tcp._fd;
        remove_node(&serv->_clients, list_find_node_p(serv->_clients, client),
        false);
        printf("[AMBER INFO] New debug client connected\n");
        return false;
    }
    return true;
}

bool amber_init_client(amber_client_t *client, amber_serv_t *serv,
    amber_world_t *world, char **arg)
{
    egg_t *egg = NULL;

    if (!check_different_mode(client, serv, arg, world))
        return false;
    egg = amber_get_egg_by_team(world, arg[0]);
    if (!egg) {
        printf("[AMBER ERROR] No egg available for team %s\n", arg[0]);
        send_cli_msg(client, "ko");
        return false;
    }
    amber_event_edi(server->_graphic_clients, egg);
    client = amber_init_client_by_egg(client, egg, world->_freq);
    snprintfizer(client, "%d", amber_get_nbr_eggs_by_team(world, arg[0]));
    snprintfizer(client, "%d %d", world->_width, world->_height);
    amber_event_pnw(client, serv->_graphic_clients);
    return true;
}

void snprintfizer(amber_client_t *client, char *format, ...)
{
    int len = 0;
    char *str = NULL;
    va_list args;
    va_list args_copy;

    va_start(args, format);
    va_copy(args_copy, args);
    len = vsnprintf(NULL, 0, format, args_copy);
    str = malloc(sizeof(char) * (len + 1));
    va_end(args_copy);
    if (!str)
        return;
    vsnprintf(str, len + 1, format, args);
    va_end(args);
    send_cli_msg(client, str);
    free(str);
}
