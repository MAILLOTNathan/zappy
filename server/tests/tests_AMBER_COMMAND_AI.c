/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_COMMAND_AI
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "amber_logic.h"
#include "amber_manage_command_ai.h"

static queue_command_t *full_queue(void)
{
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    queue_command_t *new = malloc(sizeof(queue_command_t));
    int i = 0;

    if (!new)
        return NULL;
    new->_command = &command;
    new->_next = NULL;
    for (queue_command_t *tmp = new; i < 10; tmp = tmp->_next) {
        tmp->_next = malloc(sizeof(queue_command_t));
        if (!tmp->_next)
            return NULL;
        tmp->_next->_command = &command;
        tmp->_next->_next = NULL;
        i++;
    }
    return new;
}

Test(amber_manage_command_ai, test_amber_manage_command_ai)
{
    box_t inventory = {._food = 0, ._linemate = 0, ._deraumere = 0, ._sibur = 0,
        ._mendiane = 0, ._phiras = 0, ._thystame = 0, ._players = 0, ._eggs = 0};
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    queue_command_t queue = {._command = &command, ._next = NULL};
    amber_client_t client = {._direction = UP, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = &inventory, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};
    char buffer[] = "Forward";
    amber_manage_command_ai(&client, buffer);
    cr_assert_str_eq(client._queue_command->_command->_arg, "Forward");
    client._queue_command = full_queue();
    amber_manage_command_ai(&client, buffer);
}

Test(amber_manage_command_ai, test_amber_manage_command_ai_not_found_in_queue)
{
    box_t inventory = {._food = 0, ._linemate = 0, ._deraumere = 0, ._sibur = 0,
        ._mendiane = 0, ._phiras = 0, ._thystame = 0, ._players = 0, ._eggs = 0};
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    queue_command_t queue = {._command = &command, ._next = NULL};
    amber_client_t client = {._direction = UP, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = &inventory, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};
    char buffer[] = "Inventory";
    amber_manage_command_ai(&client, buffer);
}

Test(amber_manage_command_ai, test_amber_manage_command_ai_invalid)
{
    box_t inventory = {._food = 0, ._linemate = 0, ._deraumere = 0, ._sibur = 0,
        ._mendiane = 0, ._phiras = 0, ._thystame = 0, ._players = 0, ._eggs = 0};
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    queue_command_t queue = {._command = &command, ._next = NULL};
    amber_client_t client = {._direction = UP, ._elapsed_time = 0,
        ._queue_command = &queue, ._inventory = &inventory, ._id = 1,
        ._x = 0, ._y = 0, ._level = 1, ._team_name = "Team1", ._buffer = NULL};
    char buffer[] = "Yes";
    amber_manage_command_ai(&client, buffer);
}

