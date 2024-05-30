/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_WORLD
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "amber_world.h"

char *local_teams[] = {"team1", "team2"};
args_t local_args = {._width = 10, ._height = 10, ._freq = 1, ._port = 8080,
    ._teams = local_teams, ._clientsNb = 2};

Test(amber_create_world, test_amber_create_world)
{
    amber_world_t *local_world = amber_create_world(&local_args);

    cr_assert_not_null(local_world);
    cr_assert_eq(local_world->_width, 10);
    cr_assert_eq(local_world->_height, 10);
    cr_assert_not_null(local_world->_case);
    for (int i = 0; i < local_world->_height; i++)
        cr_assert_not_null(local_world->_case[i]);
    destroy_amber_world(local_world);
}

Test(amber_refill_world, test_amber_refill_world)
{
    amber_world_t *local_world = amber_create_world(&local_args);

    amber_refill_world(local_world);
    cr_assert_eq(local_world->_food_info._c_value, 50);
    destroy_amber_world(local_world);
}

Test(amber_display_world, test_amber_display_world, .init = cr_redirect_stdout)
{
    amber_world_t *local_world = amber_create_world(&local_args);

    amber_display_world(local_world, true);
    amber_display_world(local_world, false);
    destroy_amber_world(local_world);
}

Test(amber_world_case_stringify, test_amber_world_case_stringify)
{
    box_t box = {._food = 1, ._linemate = 1, ._deraumere = 1, ._sibur = 1,
        ._mendiane = 1, ._phiras = 1, ._thystame = 1, ._players = 1, ._eggs = 1};
    char *result = amber_world_case_stringify(&box);

    cr_assert_str_eq(result, "food linemate deraumere sibur mendiane phiras thystame player egg");
}

Test(amber_create_egg, test_amber_create_egg)
{
    amber_world_t *local_world = amber_create_world(&local_args);
    egg_t *egg = NULL;

    push_back_list(local_world->_eggs, local_world, 0, 0, "team1", 0);
    for (linked_list_t *tmp = local_world->_eggs->nodes; tmp != NULL; tmp = tmp->next) {
        egg = (egg_t *)tmp->data;
    }
    cr_assert_eq(egg->_x, 0);
    cr_assert_eq(egg->_y, 0);
    cr_assert_str_eq(egg->_team, "team1");
    cr_assert_eq(egg->_id, 0);
    destroy_amber_world(local_world);
}

Test(amber_destroy_egg, test_amber_destroy_egg)
{
    egg_t *egg = malloc(sizeof(egg_t));

    egg->_x = 0;
    egg->_y = 0;
    egg->_team = strdup("team1");
    egg->_id = 0;
    amber_destroy_egg(egg);
    egg = NULL;
    amber_destroy_egg(egg);
}

Test(amber_get_egg_by_team, test_amber_get_egg_by_team)
{
    amber_world_t *local_world = amber_create_world(&local_args);
    egg_t *egg = NULL;

    push_back_list(local_world->_eggs, local_world, 0, 0, "team1", 0);
    egg = amber_get_egg_by_team(local_world, "team1");
    cr_assert_str_eq(egg->_team, "team1");
    egg = amber_get_egg_by_team(local_world, "etib");
    cr_assert_null(egg);
    local_world->_eggs->nodes = NULL;
    egg = amber_get_egg_by_team(local_world, "team1");
    cr_assert_null(egg);
    destroy_amber_world(local_world);
}
