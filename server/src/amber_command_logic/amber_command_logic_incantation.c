/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_incantation
*/

#include "amber_logic.h"
#include "amber_command_graphical.h"

static const box_t *elevation_needs[] = {
    &(box_t){._players = 1, ._linemate = 1, ._deraumere = 0, ._sibur = 0,
        ._mendiane = 0, ._phiras = 0, ._thystame = 0},
    &(box_t){._players = 2, ._linemate = 1, ._deraumere = 1, ._sibur = 1,
        ._mendiane = 0, ._phiras = 0, ._thystame = 0},
    &(box_t){._players = 2, ._linemate = 2, ._deraumere = 0, ._sibur = 1,
        ._mendiane = 0, ._phiras = 2, ._thystame = 0},
    &(box_t){._players = 4, ._linemate = 1, ._deraumere = 1, ._sibur = 2,
        ._mendiane = 0, ._phiras = 1, ._thystame = 0},
    &(box_t){._players = 4, ._linemate = 1, ._deraumere = 2, ._sibur = 1,
        ._mendiane = 3, ._phiras = 0, ._thystame = 0},
    &(box_t){._players = 6, ._linemate = 1, ._deraumere = 2, ._sibur = 3,
        ._mendiane = 0, ._phiras = 1, ._thystame = 0},
    &(box_t){._players = 6, ._linemate = 2, ._deraumere = 2, ._sibur = 2,
        ._mendiane = 2, ._phiras = 2, ._thystame = 1}
};

static bool ressource_available(box_t *world_case, const box_t *need)
{
    if (world_case->_linemate < need->_linemate)
        return false;
    if (world_case->_deraumere < need->_deraumere)
        return false;
    if (world_case->_sibur < need->_sibur)
        return false;
    if (world_case->_mendiane < need->_mendiane)
        return false;
    if (world_case->_phiras < need->_phiras)
        return false;
    if (world_case->_thystame < need->_thystame)
        return false;
    return true;
}

static bool nbr_players_on_case_lvl(amber_serv_t *serv, amber_client_t *client,
    int need_players)
{
    linked_list_t *clients = serv->_clients->nodes;
    amber_client_t *tmp = NULL;
    int count = 0;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_level != client->_level)
            continue;
        if (tmp->_x == client->_x && tmp->_y == client->_y &&
            tmp->_is_incantating)
            count++;
    }
    return count >= need_players;
}

static void print_res_incantation(amber_client_t *client, int level)
{
    snprintfizer(client, "Current level: %d", level);
}

static void level_up_players(amber_client_t *client, amber_serv_t *server)
{
    linked_list_t *clients = server->_clients->nodes;
    amber_client_t *tmp = NULL;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_level != client->_level || tmp->_id == client->_id)
            continue;
        if (tmp->_x == client->_x && tmp->_y == client->_y &&
            tmp->_is_incantating) {
            tmp->_level++;
            print_res_incantation(tmp, tmp->_level);
            tmp->_is_incantating = false;
        }
    }
    client->_level++;
    print_res_incantation(client, client->_level);
    client->_is_incantating = false;
    amber_event_pie(client, server->_graphic_clients, true);
}

static void remove_from_info_world(amber_world_t *world, amber_client_t *cli,
    const box_t *needs)
{
    world->_case[cli->_y][cli->_x]._linemate -= needs->_linemate;
    world->_case[cli->_y][cli->_x]._deraumere -= needs->_deraumere;
    world->_case[cli->_y][cli->_x]._sibur -= needs->_sibur;
    world->_case[cli->_y][cli->_x]._mendiane -= needs->_mendiane;
    world->_case[cli->_y][cli->_x]._phiras -= needs->_phiras;
    world->_case[cli->_y][cli->_x]._thystame -= needs->_thystame;
    world->_food_info._c_value -= needs->_food;
    world->_linemate_info._c_value -= needs->_linemate;
    world->_deraumere_info._c_value -= needs->_deraumere;
    world->_sibur_info._c_value -= needs->_sibur;
    world->_mendiane_info._c_value -= needs->_mendiane;
    world->_phiras_info._c_value -= needs->_phiras;
    world->_thystame_info._c_value -= needs->_thystame;
}

static void incation_failed(amber_client_t *client, amber_serv_t *serv)
{
    linked_list_t *node = serv->_clients->nodes;
    amber_client_t *tmp = NULL;

    for (; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_x != client->_x || tmp->_y != client->_y)
            continue;
        if (tmp->_level != client->_level || tmp->_id == client->_id ||
            !tmp->_is_incantating || tmp->_team_name == NULL)
            continue;
        tmp->_is_incantating = false;
    }
    client->_is_incantating = false;
    send_cli_msg(client, "ko");
}

void amber_logic_incantation(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    const box_t *needs = elevation_needs[client->_level - 1];

    if (!ressource_available(&world->_case[client->_y][client->_x],
        needs)) {
        return incation_failed(client, serv);
    }
    if (!nbr_players_on_case_lvl(serv, client, needs->_players)) {
        return incation_failed(client, serv);
    }
    remove_from_info_world(world, client, needs);
    level_up_players(client, serv);
}
