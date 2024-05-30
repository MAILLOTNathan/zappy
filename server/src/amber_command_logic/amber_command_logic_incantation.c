/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_incantation
*/

#include "amber_logic.h"

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
    if (world_case->_food < need->_food)
        return false;
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
        if (tmp->_x == client->_x && tmp->_y == client->_y)
            count++;
    }
    return count >= need_players;
}

static void level_up_players(amber_client_t *client, amber_serv_t *server)
{
    linked_list_t *clients = server->_clients->nodes;
    amber_client_t *tmp = NULL;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_level != client->_level || tmp->_id == client->_id)
            continue;
        if (tmp->_x == client->_x && tmp->_y == client->_y) {
            tmp->_level++;
            dprintf(tmp->_tcp._fd, "Elevation underway\n");
            dprintf(tmp->_tcp._fd, "Current level: %d\n", tmp->_level);
        }
        tmp->_is_incantating = false;
    }
    client->_level++;
    dprintf(client->_tcp._fd, "Elevation underway\n");
    dprintf(client->_tcp._fd, "Current level: %d\n", client->_level);
    client->_is_incantating = false;
}

void amber_logic_incantation(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    const box_t *needs = elevation_needs[client->_level - 1];

    if (!ressource_available(&world->_case[client->_y][client->_x],
        needs)) {
        dprintf(client->_tcp._fd, "ko\n");
        return;
    }
    if (!nbr_players_on_case_lvl(serv, client, needs->_players)) {
        dprintf(client->_tcp._fd, "ko\n");
        return;
    }
    world->_case[client->_y][client->_x]._linemate -= needs->_linemate;
    world->_case[client->_y][client->_x]._deraumere -= needs->_deraumere;
    world->_case[client->_y][client->_x]._sibur -= needs->_sibur;
    world->_case[client->_y][client->_x]._mendiane -= needs->_mendiane;
    world->_case[client->_y][client->_x]._phiras -= needs->_phiras;
    world->_case[client->_y][client->_x]._thystame -= needs->_thystame;
    level_up_players(client, serv);
}
