/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_logic_take_set
*/

#include "amber_logic.h"
#include "amber_command_graphical.h"

static void change_inventory(amber_trantor_t *trantor,
    box_t *ressource, bool mode)
{
    if (mode) {
        trantor->_inventory->_food += ressource->_food;
        trantor->_inventory->_linemate += ressource->_linemate;
        trantor->_inventory->_deraumere += ressource->_deraumere;
        trantor->_inventory->_sibur += ressource->_sibur;
        trantor->_inventory->_mendiane += ressource->_mendiane;
        trantor->_inventory->_phiras += ressource->_phiras;
        trantor->_inventory->_thystame += ressource->_thystame;
    } else {
        trantor->_inventory->_food -= ressource->_food;
        trantor->_inventory->_linemate -= ressource->_linemate;
        trantor->_inventory->_deraumere -= ressource->_deraumere;
        trantor->_inventory->_sibur -= ressource->_sibur;
        trantor->_inventory->_mendiane -= ressource->_mendiane;
        trantor->_inventory->_phiras -= ressource->_phiras;
        trantor->_inventory->_thystame -= ressource->_thystame;
    }
}

static bool ressource_available(box_t *world_case, box_t *need)
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

static bool take_ressource(amber_trantor_t *cli, amber_world_t *world,
    box_t *need)
{
    box_t *copy = &world->_case[cli->_y][cli->_x];

    if (!ressource_available(copy, need))
        return false;
    world->_case[cli->_y][cli->_x]._food -= copy->_food >= 1 ? need->_food : 0;
    world->_case[cli->_y][cli->_x]._linemate -=
        copy->_linemate >= 1 ? need->_linemate : 0;
    world->_case[cli->_y][cli->_x]._deraumere -=
        copy->_deraumere >= 1 ? need->_deraumere : 0;
    world->_case[cli->_y][cli->_x]._sibur -=
        copy->_sibur >= 1 ? need->_sibur : 0;
    world->_case[cli->_y][cli->_x]._mendiane -=
        copy->_mendiane >= 1 ? need->_mendiane : 0;
    world->_case[cli->_y][cli->_x]._phiras -=
        copy->_phiras >= 1 ? need->_phiras : 0;
    world->_case[cli->_y][cli->_x]._thystame -=
        copy->_thystame >= 1 ? need->_thystame : 0;
    change_inventory(cli, need, true);
    return true;
}

static box_t *get_ressource_needed(char *request)
{
    box_t *ressource_needed = amber_world_case_init();

    if (strcmp(request, "food") == 0)
        ressource_needed->_food = 1;
    if (strcmp(request, "linemate") == 0)
        ressource_needed->_linemate = 1;
    if (strcmp(request, "deraumere") == 0)
        ressource_needed->_deraumere = 1;
    if (strcmp(request, "sibur") == 0)
        ressource_needed->_sibur = 1;
    if (strcmp(request, "mendiane") == 0)
        ressource_needed->_mendiane = 1;
    if (strcmp(request, "phiras") == 0)
        ressource_needed->_phiras = 1;
    if (strcmp(request, "thystame") == 0)
        ressource_needed->_thystame = 1;
    return ressource_needed;
}

static void drop_ressource_from_world(amber_world_t *world, box_t *res)
{
    world->_food_info._c_value += res->_food;
    world->_linemate_info._c_value += res->_linemate;
    world->_deraumere_info._c_value += res->_deraumere;
    world->_sibur_info._c_value += res->_sibur;
    world->_mendiane_info._c_value += res->_mendiane;
    world->_phiras_info._c_value += res->_phiras;
    world->_thystame_info._c_value += res->_thystame;
}

void amber_logic_take(amber_net_cli_t *client, amber_world_t *world,
    amber_serv_t *serv)
{
    char *request = TRANTOR(client)->_queue_command->_command->_arg;
    box_t *ressource_needed = get_ressource_needed(request);

    if (take_ressource(TRANTOR(client), world, ressource_needed)) {
        world->_food_info._c_value -= ressource_needed->_food;
        world->_linemate_info._c_value -= ressource_needed->_linemate;
        world->_deraumere_info._c_value -= ressource_needed->_deraumere;
        world->_sibur_info._c_value -= ressource_needed->_sibur;
        world->_mendiane_info._c_value -= ressource_needed->_mendiane;
        world->_phiras_info._c_value -= ressource_needed->_phiras;
        world->_thystame_info._c_value -= ressource_needed->_thystame;
        amber_event_pgt(client, serv->_graphic_clients, ressource_needed);
        return send_cli_msg(client, "ok");
    }
    return send_cli_msg(client, "ko");
}

void update_world_case(amber_world_t *world, amber_trantor_t *trantor,
    box_t *ressource_needed)
{
    world->_case[trantor->_y][trantor->_x]._food += ressource_needed->_food;
    world->_case[trantor->_y][trantor->_x]._linemate +=
        ressource_needed->_linemate;
    world->_case[trantor->_y][trantor->_x]._deraumere +=
        ressource_needed->_deraumere;
    world->_case[trantor->_y][trantor->_x]._sibur += ressource_needed->_sibur;
    world->_case[trantor->_y][trantor->_x]._mendiane +=
        ressource_needed->_mendiane;
    world->_case[trantor->_y][trantor->_x]._phiras +=
        ressource_needed->_phiras;
    world->_case[trantor->_y][trantor->_x]._thystame +=
        ressource_needed->_thystame;
}

void amber_logic_set(amber_net_cli_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    amber_trantor_t *trantor = TRANTOR(client);
    char *request = trantor->_queue_command->_command->_arg;
    box_t *ressource_needed = get_ressource_needed(request);

    if (!ressource_available(trantor->_inventory, ressource_needed))
        return send_cli_msg(client, "ko");
    update_world_case(world, trantor, ressource_needed);
    change_inventory(TRANTOR(client), ressource_needed, false);
    drop_ressource_from_world(world, ressource_needed);
    amber_event_pdr(client, serv->_graphic_clients, ressource_needed);
    return send_cli_msg(client, "ok");
}
