/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_QUEUE
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "amber_queue_command.h"

Test(queue_push_back, test_queue_push_back)
{
    queue_command_t *queue = NULL;
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    command_t command2 = {._arg = "Right", ._id = 1, ._time = 7};

    cr_assert_eq(queue_push_back(&queue, &command), true);
    cr_assert_str_eq(queue->_command->_arg, "Forward");
    cr_assert_eq(queue_push_back(&queue, &command2), true);
    queue->_command = NULL;
    cr_assert_eq(queue_push_back(&queue, &command), true);
}

Test(queue_push_back_d, test_queue_push_back_d)
{
    queue_command_t *queue = NULL;

    cr_assert_eq(queue_push_back_d(&queue, "Forward", 7, 1), true);
    cr_assert_str_eq(queue->_command->_arg, "Forward");
    cr_assert_eq(queue_push_back_d(&queue, "Right", 7, 1), true);
    queue->_command = NULL;
    cr_assert_eq(queue_push_back_d(&queue, "Forward", 7, 1), true);
}

Test(queue_pop_front, test_queue_pop_front)
{
    queue_command_t *queue = NULL;
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    command_t command2 = {._arg = "Right", ._id = 1, ._time = 7};

    queue_push_back(&queue, &command);
    queue_push_back(&queue, &command2);
    cr_assert_str_eq(queue_pop_front(&queue)->_arg, "Forward");
    cr_assert_str_eq(queue_pop_front(&queue)->_arg, "Right");
    cr_assert_null(queue_pop_front(&queue));
}

Test(queue_destroy, test_queue_destroy)
{
    queue_command_t *queue = NULL;
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    command_t command2 = {._arg = "Right", ._id = 1, ._time = 7};

    queue_push_back(&queue, &command);
    queue_push_back(&queue, &command2);
    queue_destroy(&queue);
    cr_assert_null(queue);
}

Test(queue_front, test_queue_front)
{
    queue_command_t *queue = NULL;
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    command_t command2 = {._arg = "Right", ._id = 1, ._time = 7};

    queue_push_back(&queue, &command);
    queue_push_back(&queue, &command2);
    cr_assert_str_eq(queue_front(queue)->_arg, "Forward");
    cr_assert_null(queue_front(NULL));
}

Test(queue_command_size, test_queue_command_size)
{
    queue_command_t *queue = NULL;
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    command_t command2 = {._arg = "Right", ._id = 1, ._time = 7};

    queue_push_back(&queue, &command);
    queue_push_back(&queue, &command2);
    cr_assert_eq(queue_command_size(queue), 2);
    cr_assert_eq(queue_command_size(NULL), 0);
}

Test(queue_display, test_queue_display)
{
    queue_command_t *queue = NULL;
    command_t command = {._arg = "Forward", ._id = 1, ._time = 7};
    command_t command2 = {._arg = "Right", ._id = 1, ._time = 7};

    queue_push_back(&queue, &command);
    queue_push_back(&queue, &command2);
    queue_display(queue);
    queue_display(NULL);
}