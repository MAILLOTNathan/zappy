/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_logic_take_set
*/

#include "amber_logic.h"

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

static void change_inventory(amber_client_t *client,
    box_t *ressource, bool mode)
{
    if (mode) {
        client->_inventory->_food += ressource->_food;
        client->_inventory->_linemate += ressource->_linemate;
        client->_inventory->_deraumere += ressource->_deraumere;
        client->_inventory->_sibur += ressource->_sibur;
        client->_inventory->_mendiane += ressource->_mendiane;
        client->_inventory->_phiras += ressource->_phiras;
        client->_inventory->_thystame += ressource->_thystame;
    } else {
        client->_inventory->_food -= ressource->_food;
        client->_inventory->_linemate -= ressource->_linemate;
        client->_inventory->_deraumere -= ressource->_deraumere;
        client->_inventory->_sibur -= ressource->_sibur;
        client->_inventory->_mendiane -= ressource->_mendiane;
        client->_inventory->_phiras -= ressource->_phiras;
        client->_inventory->_thystame -= ressource->_thystame;
    }
}

static bool take_ressource(amber_client_t *cli, amber_world_t *world,
    box_t *need)
{
    box_t *copy = &world->_case[cli->_y][cli->_x];

    if (!ressource_available(copy, need))
        return false;
    world->_case[cli->_y][cli->_x]._food -= copy->_food >= need->_food ? 1 : 0;
    world->_case[cli->_y][cli->_x]._linemate -=
        copy->_linemate >= need->_linemate ? 1 : 0;
    world->_case[cli->_y][cli->_x]._deraumere -=
        copy->_deraumere >= need->_deraumere ? 1 : 0;
    world->_case[cli->_y][cli->_x]._sibur -=
        copy->_sibur >= need->_sibur ? 1 : 0;
    world->_case[cli->_y][cli->_x]._mendiane -=
        copy->_mendiane >= need->_mendiane ? 1 : 0;
    world->_case[cli->_y][cli->_x]._phiras -=
        copy->_phiras >= need->_phiras ? 1 : 0;
    world->_case[cli->_y][cli->_x]._thystame -=
        copy->_thystame >= need->_thystame ? 1 : 0;
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

void amber_logic_take(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    char *request = client->_queue_command->_command->_arg;
    box_t *ressource_needed = get_ressource_needed(request);

    if (take_ressource(client, world, ressource_needed))
        return send_client_message(client, "ok\n");
    return send_client_message(client, "ko\n");
}

void amber_logic_set(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    char *request = client->_queue_command->_command->_arg;
    box_t *ressource_needed = get_ressource_needed(request);

    if (!ressource_available(client->_inventory, ressource_needed))
        return send_client_message(client, "ko\n");
    world->_case[client->_y][client->_x]._food += ressource_needed->_food;
    world->_case[client->_y][client->_x]._linemate +=
        ressource_needed->_linemate;
    world->_case[client->_y][client->_x]._deraumere +=
        ressource_needed->_deraumere;
    world->_case[client->_y][client->_x]._sibur += ressource_needed->_sibur;
    world->_case[client->_y][client->_x]._mendiane +=
        ressource_needed->_mendiane;
    world->_case[client->_y][client->_x]._phiras += ressource_needed->_phiras;
    world->_case[client->_y][client->_x]._thystame +=
        ressource_needed->_thystame;
    change_inventory(client, ressource_needed, false);
    return send_client_message(client, "ok\n");
}
