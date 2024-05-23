/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_WORLD
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "amber_world.h"

Test(amber_create_world, test_amber_create_world)
{
    amber_world_t *world = amber_create_world(10, 10);

    cr_assert_not_null(world);
    cr_assert_eq(world->_width, 10);
    cr_assert_eq(world->_height, 10);
    cr_assert_not_null(world->_case);
    for (int i = 0; i < world->_height; i++)
        cr_assert_not_null(world->_case[i]);
    destroy_amber_world(world);
}

Test(amber_refill_world, test_amber_refill_world)
{
    amber_world_t *world = amber_create_world(10, 10);

    amber_refill_world(world);
    cr_assert_eq(world->_food_info._c_value, 50);
    destroy_amber_world(world);
}

Test(amber_display_world, test_amber_display_world, .init = cr_redirect_stdout)
{
    amber_world_t *world = amber_create_world(10, 10);

    amber_display_world(world, true);
    amber_display_world(world, false);
    destroy_amber_world(world);
}
