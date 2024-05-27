/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_COMMAND_LOGIC
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "amber_logic.h"

char *teams[] = {"team1", "team2"};
args_t args = {._width = 10, ._height = 10, ._freq = 1, ._port = 9001,
    ._teams = teams, ._clientsNb = 2};

command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
queue_command_t queue = {._command = &command, ._next = NULL};

Test(amber_logic_look, test_look_up)
{
    amber_world_t *world = amber_create_world(&args);
    amber_client_t client = {._direction = UP, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = NULL, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};

    amber_logic_look(&client, world);
    destroy_amber_world(world);
    world = NULL;
    destroy_amber_world(world);
}

Test(amber_logic_look, test_look_down)
{
    amber_world_t *world = amber_create_world(&args);
    amber_client_t client = {._direction = DOWN, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = NULL, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};

    amber_logic_look(&client, world);
    destroy_amber_world(world);
}

Test(amber_logic_look, test_look_left)
{
    amber_world_t *world = amber_create_world(&args);
    amber_client_t client = {._direction = LEFT, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = NULL, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};

    amber_logic_look(&client, world);
    destroy_amber_world(world);
}

Test(amber_logic_look, test_look_right)
{
    amber_world_t *world = amber_create_world(&args);
    amber_client_t client = {._direction = RIGHT, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = NULL, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};

    amber_logic_look(&client, world);
    destroy_amber_world(world);
}

Test(amber_logic_inventory, test_inventory)
{
    amber_world_t *world = amber_create_world(&args);
    box_t inventory = {._food = 0, ._linemate = 0, ._deraumere = 0, ._sibur = 0,
    ._mendiane = 0, ._phiras = 0, ._thystame = 0, ._players = 0, ._eggs = 0};
    amber_client_t client = {._direction = RIGHT, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = &inventory, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};
    char *result = malloc(sizeof(char) * 1024);

    sprintf(result, INVENTORY, inventory._food, inventory._linemate,
        inventory._deraumere, inventory._sibur, inventory._mendiane,
        inventory._phiras, inventory._thystame);
    amber_logic_inventory(&client, world);
    cr_assert_str_eq(result, "[food 0, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 0, thystame 0]\n");
    free(result);
    destroy_amber_world(world);
}

Test(amber_check_client_alive, test_amber_check_client_alive)
{
    amber_serv_t *server = amber_create_server(&args);
    amber_world_t *world = amber_create_world(&args);

    push_back_list(server->_clients, 42, world->_eggs->nodes->data);
    ((amber_client_t *)server->_clients->nodes->data)->_inventory->_food = -1;
    amber_check_client_alive(server);
    cr_assert_eq(server->_clients->nodes, NULL);
    destroy_amber_world(world);
}

Test(clamp, test_clamp)
{
    cr_assert_eq(clamp(1, 0, 10), 9);
    cr_assert_eq(clamp(0, 0, 10), 0);
    cr_assert_eq(clamp(0, 5, 10), 5);
    cr_assert_eq(clamp(1, 12, 10), 3);
}

Test(real_clamp, test_real_clamp)
{
    cr_assert_eq(real_clamp(1, 0, 10), 1);
    cr_assert_eq(real_clamp(0, 0, 10), 0);
    cr_assert_eq(real_clamp(0, 5, 10), 5);
    cr_assert_eq(real_clamp(1, 12, 10), 10);
}

Test(amber_logic_forward, test_amber_logic_forward)
{
    amber_world_t *world = amber_create_world(&args);
    amber_client_t client = {._direction = UP, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = NULL, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};

    amber_logic_forward(&client, world);
    cr_assert_eq(client._y, 1);
    cr_assert_eq(client._x, 0);
    client._direction = DOWN;
    amber_logic_forward(&client, world);
    cr_assert_eq(client._y, 0);
    cr_assert_eq(client._x, 0);
    client._direction = LEFT;
    amber_logic_forward(&client, world);
    cr_assert_eq(client._y, 0);
    cr_assert_eq(client._x, 9);
    client._direction = RIGHT;
    amber_logic_forward(&client, world);
    cr_assert_eq(client._y, 0);
    cr_assert_eq(client._x, 0);
    client._y = 9;
    client._direction = UP;
    amber_logic_forward(&client, world);
    cr_assert_eq(client._y, 0);
    cr_assert_eq(client._x, 0);
    destroy_amber_world(world);
}

Test(amber_logic_right, test_amber_logic_right)
{
    amber_client_t client = {._direction = UP, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = NULL, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};

    amber_logic_right(&client, NULL);
    cr_assert_eq(client._direction, RIGHT);
    amber_logic_right(&client, NULL);
    cr_assert_eq(client._direction, DOWN);
    amber_logic_right(&client, NULL);
    cr_assert_eq(client._direction, LEFT);
    amber_logic_right(&client, NULL);
    cr_assert_eq(client._direction, UP);
}

Test(amber_logic_left, test_amber_logic_left)
{
    amber_client_t client = {._direction = UP, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = NULL, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};

    amber_logic_left(&client, NULL);
    cr_assert_eq(client._direction, LEFT);
    amber_logic_left(&client, NULL);
    cr_assert_eq(client._direction, DOWN);
    amber_logic_left(&client, NULL);
    cr_assert_eq(client._direction, RIGHT);
    amber_logic_left(&client, NULL);
    cr_assert_eq(client._direction, UP);
}