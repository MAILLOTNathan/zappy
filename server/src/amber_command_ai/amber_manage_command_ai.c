/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_command_ai
*/

#include "amber_manage_command_ai.h"

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

static void update_players_on_case(amber_serv_t *serv, amber_client_t *client)
{
    linked_list_t *clients = serv->_clients->nodes;
    amber_client_t *tmp = NULL;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_client_t *)node->data;
        if (tmp->_level != client->_level)
            continue;
        if (tmp->_x == client->_x && tmp->_y == client->_y)
            tmp->_is_incantating = true;
    }
}

static bool check_incanation(amber_world_t *world, amber_serv_t *serv,
    amber_client_t *client)
{
    const box_t *needs = elevation_needs[client->_level - 1];

    if (!ressource_available(&world->_case[client->_y][client->_x],
        needs)) {
        dprintf(client->_tcp._fd, "ko\n");
        return false;
    }
    if (!nbr_players_on_case_lvl(serv, client, needs->_players)) {
        dprintf(client->_tcp._fd, "ko\n");
        return false;
    }
    update_players_on_case(serv, client);
    return true;
}

void amber_manage_command_ai(amber_world_t *world, amber_serv_t *serv,
    amber_client_t *client, char **arg)
{
    int i = 0;

    if (queue_command_size(client->_queue_command) >= 10) {
        dprintf(client->_tcp._fd, "ko\n");
        return;
    }
    if (strcmp(arg[0], "Incantation") == 0 &&
        !check_incanation(world, serv, client))
        return;
    for (i = 0; ai_commands[i]._command; i++) {
        if (strcmp(ai_commands[i]._command, arg[0]) == 0) {
            ai_commands[i]._func(client, arg);
            break;
        }
    }
    if (ai_commands[i]._command == NULL)
        dprintf(client->_tcp._fd, "ko\n");
    else
        printf("[AMBER AI] Command recevei %s\n", arg[0]);
}

const ai_command_t ai_commands[] = {
    {"Forward", T_FORWARD, &amber_ai_forward},
    {"Right", T_RIGHT, &amber_ai_right},
    {"Left", T_LEFT, &amber_ai_left},
    {"Look", T_LOOK, &amber_ai_look},
    {"Inventory", T_INVENTORY, &amber_ai_inventory},
    {"Connect_nbr", T_CONNECT_NBR, &amber_ai_connect_nbr},
    {"Broadcast", T_BROADCAST, &amber_ai_broadcast},
    {"Eject", T_EJECT, &amber_ai_eject},
    {"Fork", T_FORK, &amber_ai_fork},
    {"Take", T_TAKE, &amber_ai_take_object},
    {"Set", T_SET, &amber_ai_set_object},
    {"Incantation", T_INCANTATION, &amber_ai_incantation},
    {NULL, -1, NULL}
};
