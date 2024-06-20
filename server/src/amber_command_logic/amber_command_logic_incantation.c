/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_incantation
*/

#include "amber_logic.h"
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

static bool nbr_players_on_case_lvl(int need_players, info_incantation_t *info)
{
    amber_net_cli_t **ids = info->_ids;
    amber_trantor_t *trantor = NULL;
    int count = 0;

    for (int i = 0; i < info->_nb_players; i++) {
        trantor = TRANTOR(ids[i]);
        if (trantor->_x == info->_x && trantor->_y == info->_y &&
            trantor->_level == info->_level)
            count++;
    }
    return count >= need_players;
}

static void print_res_incantation(amber_net_cli_t *client, int level,
    amber_serv_t *server)
{
    snprintfizer(client, "Current level: %d", level);
    amber_event_idmoved(client, server->_graphic_clients, 'I');
}

static void level_up_players(info_incantation_t *info, amber_serv_t *serv)
{
    amber_net_cli_t **ids = info->_ids;
    amber_trantor_t *trantor = NULL;

    for (int i = 0; i < info->_nb_players; i++) {
        trantor = TRANTOR(ids[i]);
        trantor->_level++;
        trantor->_is_incantating = false;
        print_res_incantation(ids[i], trantor->_level, serv);
    }
}

static void remove_from_info_world(amber_world_t *world, amber_trantor_t *trt,
    const box_t *needs)
{
    world->_case[trt->_y][trt->_x]._linemate -= needs->_linemate;
    world->_case[trt->_y][trt->_x]._deraumere -= needs->_deraumere;
    world->_case[trt->_y][trt->_x]._sibur -= needs->_sibur;
    world->_case[trt->_y][trt->_x]._mendiane -= needs->_mendiane;
    world->_case[trt->_y][trt->_x]._phiras -= needs->_phiras;
    world->_case[trt->_y][trt->_x]._thystame -= needs->_thystame;
    world->_food_info._c_value -= needs->_food;
    world->_linemate_info._c_value -= needs->_linemate;
    world->_deraumere_info._c_value -= needs->_deraumere;
    world->_sibur_info._c_value -= needs->_sibur;
    world->_mendiane_info._c_value -= needs->_mendiane;
    world->_phiras_info._c_value -= needs->_phiras;
    world->_thystame_info._c_value -= needs->_thystame;
}

static void incantion_failed(amber_world_t *world, info_incantation_t *info)
{
    amber_net_cli_t **ids = info->_ids;

    for (int i = 0; i < info->_nb_players; i++) {
        TRANTOR(ids[i])->_is_incantating = false;
        send_cli_msg(ids[i], "ko");
    }
    remove_node(&world->_incantation_grp,
        world->_incantation_grp->nodes, true);
}

void amber_logic_incantation(amber_net_cli_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    amber_trantor_t *trantor = TRANTOR(client);
    const box_t *needs = elevation_needs[trantor->_level - 1];
    info_incantation_t *info = world->_incantation_grp->nodes->data;

    if (info->_y != trantor->_y || info->_x != trantor->_x)
        return incantion_failed(world, info);
    if (!ressource_available(&world->_case[trantor->_y][trantor->_x],
        needs))
        return incantion_failed(world, info);
    if (!nbr_players_on_case_lvl(needs->_players, info))
        return incantion_failed(world, info);
    remove_from_info_world(world, client, needs);
    level_up_players(info, serv);
    remove_node(&world->_incantation_grp,
        world->_incantation_grp->nodes, true);
}
