/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_command_ai
*/

#include "amber_manage_command_ai.h"
#include "amber_command_graphical.h"
#include "amber_manage_incantation.h"

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

static bool nbr_players_on_case_lvl(amber_serv_t *serv,
    amber_trantor_t *trantor, int need_players)
{
    linked_list_t *clients = serv->_clients->nodes;
    amber_net_cli_t *tmp = NULL;
    int count = 0;
    amber_trantor_t *t_tmp = NULL;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_net_cli_t *)node->data;
        if (tmp->_type != AI)
            continue;
        t_tmp = TRANTOR(tmp);
        if (t_tmp->_level != trantor->_level || trantor->_is_incantating)
            continue;
        if (t_tmp->_x == trantor->_x && t_tmp->_y == trantor->_y)
            count++;
    }
    return count >= need_players;
}

static info_incantation_t *update_players_on_case(amber_serv_t *serv,
    amber_trantor_t *trantor, amber_net_cli_t *client)
{
    linked_list_t *clients = serv->_clients->nodes;
    amber_net_cli_t *tmp = NULL;
    info_incantation_t *info = amber_init_info_incantation(trantor);
    amber_trantor_t *t_tmp = NULL;

    for (linked_list_t *node = clients; node; node = node->next) {
        tmp = (amber_net_cli_t *)node->data;
        if (tmp->_type != AI)
            continue;
        t_tmp = TRANTOR(client);
        if (t_tmp->_level != trantor->_level || t_tmp->_is_incantating)
            continue;
        if (t_tmp->_x == trantor->_x && t_tmp->_y == trantor->_y)
            amber_add_player_to_incantation(info, tmp);
    }
    return info;
}

static bool check_incanation(amber_world_t *world, amber_serv_t *serv,
    amber_net_cli_t *client, amber_trantor_t *trantor)
{
    const box_t *needs = elevation_needs[trantor->_level - 1];
    info_incantation_t *info = NULL;

    if (trantor->_level == 8)
        return false;
    if (!ressource_available(&world->_case[trantor->_y][trantor->_x],
        needs)) {
        send_cli_msg(client, "ko");
        return false;
    }
    if (!nbr_players_on_case_lvl(serv, client, needs->_players)) {
        send_cli_msg(client, "ko");
        return false;
    }
    info = update_players_on_case(serv, trantor, client);
    push_back_list(world->_incantation_grp, info);
    return true;
}

void check_ellapsed_time(amber_trantor_t *trantor, double freq)
{
    if (queue_command_size(trantor->_queue_command) != 1)
        return;
    trantor->_ellapsed_time = get_new_time_in_microseconds(
        trantor->_queue_command->_command->_time / freq);
}

bool check_command_queue(amber_net_cli_t *client, amber_trantor_t *trantor,
    char **arg)
{
    if (queue_command_size(trantor->_queue_command) >= 10) {
        send_cli_msg(client, "ko");
        return false;
    }
    return true;
}

void amber_manage_command_ai(amber_world_t *world, amber_serv_t *serv,
    amber_net_cli_t *client, char **arg)
{
    int i = 0;
    amber_trantor_t *trantor = TRANTOR(client);

    printf("[AMBER AI] Command recevei %s BY %d\n", arg[0], client->_id);
    if (!check_command_queue(client, trantor, arg))
        return;
    if (strcmp(arg[0], "Incantation") == 0 &&
        !check_incanation(world, serv, client))
        return;
    for (i = 0; ai_commands[i]._command; i++) {
        if (strcmp(ai_commands[i]._command, arg[0]) == 0) {
            ai_commands[i]._func(client, arg);
            return check_ellapsed_time(trantor, world->_freq);
        }
    }
    send_cli_msg(client, "ko");
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
