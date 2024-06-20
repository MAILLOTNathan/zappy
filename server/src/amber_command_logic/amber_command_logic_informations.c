/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_logic_informations
*/

#include "amber_logic.h"
#include "string_array.h"
#include "amber_manage_client.h"

static char *switch_string(amber_world_t *world, int y, int x)
{
    char *tmp = amber_world_case_stringify(&world->_case[y][x]);

    tmp = !tmp ? strdup("") : tmp;
    return tmp;
}

static char **amber_look_up(amber_trantor_t *trantor, amber_world_t *world)
{
    int start_y = clamp(0, trantor->_y - trantor->_level, world->_height);
    int start_x = clamp(0, trantor->_x + trantor->_level, world->_width);
    int offset = 0;
    int x = 0;
    int y = 0;
    char **result = NULL;

    for (int i = trantor->_level; i > 0; i--) {
        y = clamp(0, start_y - offset, world->_height);
        y = y == world->_height ? 0 : y;
        for (int j = 0; i * 2 + 1 > j; j++) {
            x = clamp(0, start_x - j - offset, world->_width);
            x = x == world->_width ? 0 : x;
            result = prepend_string_array(result, switch_string(world, y, x));
        }
        offset++;
    }
    result = prepend_string_array(result, switch_string(world, trantor->_y,
    trantor->_x));
    return result;
}

static char **amber_look_left(amber_trantor_t *trantor, amber_world_t *world)
{
    int start_y = clamp(0, trantor->_y - trantor->_level, world->_height);
    int start_x = clamp(0, trantor->_x - trantor->_level, world->_width);
    int offset = 0;
    int x = 0;
    int y = 0;
    char **result = NULL;

    for (int i = trantor->_level; i > 0; i--) {
        x = clamp(0, start_x + offset, world->_width);
        x = x == world->_width ? 0 : x;
        for (int j = 0; i * 2 + 1 > j; j++) {
            y = clamp(0, start_y + j + offset, world->_height);
            y = y == world->_height ? 0 : y;
            result = prepend_string_array(result, switch_string(world, y, x));
        }
        offset++;
    }
    result = prepend_string_array(result, switch_string(world, trantor->_y,
    trantor->_x));
    return result;
}

static char **amber_look_down(amber_trantor_t *trantor, amber_world_t *world)
{
    int start_y = clamp(0, trantor->_y + trantor->_level, world->_height);
    int start_x = clamp(0, trantor->_x - trantor->_level, world->_width);
    int offset = 0;
    int x = 0;
    int y = 0;
    char **result = NULL;

    for (int i = trantor->_level; i > 0; i--) {
        y = clamp(0, start_y - offset, world->_height);
        y = y == world->_height ? 0 : y;
        for (int j = 0; i * 2 + 1 > j; j++) {
            x = clamp(0, start_x + j + offset, world->_width);
            x = x == world->_width ? 0 : x;
            result = prepend_string_array(result, switch_string(world, y, x));
        }
        offset++;
    }
    result = prepend_string_array(result, switch_string(world, trantor->_y,
    trantor->_x));
    return result;
}

static char **amber_look_right(amber_trantor_t *trantor, amber_world_t *world)
{
    int start_y = clamp(0, trantor->_y + trantor->_level, world->_height);
    int start_x = clamp(0, trantor->_x + trantor->_level, world->_width);
    int offset = 0;
    int x = 0;
    int y = 0;
    char **result = NULL;

    for (int i = trantor->_level; i > 0; i--) {
        x = clamp(0, start_x - offset, world->_width);
        x = x == world->_width ? 0 : x;
        for (int j = 0; i * 2 + 1 > j; j++) {
            y = clamp(0, start_y - j - offset, world->_height);
            y = y == world->_height ? 0 : y;
            result = prepend_string_array(result, switch_string(world, y, x));
        }
        offset++;
    }
    result = prepend_string_array(result, switch_string(world, trantor->_y,
    trantor->_x));
    return result;
}

void amber_logic_look(amber_net_cli_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    char **result = NULL;
    char *response = NULL;

    switch (TRANTOR(client)->_direction) {
        case UP:
            result = amber_look_up(TRANTOR(client), world);
            break;
        case LEFT:
            result = amber_look_left(TRANTOR(client), world);
            break;
        case DOWN:
            result = amber_look_down(TRANTOR(client), world);
            break;
        case RIGHT:
            result = amber_look_right(TRANTOR(client), world);
    }
    response = string_array_to_string_separator(result, ',');
    snprintfizer(client, "[%s]", response);
    free_string_array(result);
    free(response);
}

void amber_logic_inventory(amber_net_cli_t *client,
    UNUSED amber_world_t *world, UNUSED amber_serv_t *serv)
{
    box_t *inv = TRANTOR(client)->_inventory;

    snprintfizer(client, "[food %d, linemate %d, deraumere %d, sibur %d, "
        "mendiane %d, phiras %d, thystame %d]", inv->_food, inv->_linemate,
        inv->_deraumere, inv->_sibur, inv->_mendiane, inv->_phiras,
        inv->_thystame);
}

void amber_logic_connect_nbr(amber_net_cli_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv)
{
    int count = amber_get_nbr_eggs_by_team(world, TRANTOR(client)->_team_name);

    snprintfizer(client, "%d", count);
}
