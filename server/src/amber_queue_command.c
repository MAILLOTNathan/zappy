/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_queue_command
*/

#include "amber_queue_command.h"

bool queue_push_back(queue_command_t **q, command_t *command)
{
    queue_command_t *new = malloc(sizeof(queue_command_t));
    queue_command_t *last = *q;

    if (!new)
        return false;
    new->_command = command;
    new->_next = NULL;
    if (*q == NULL) {
        *q = new;
        return true;
    }
    while (last->_next != NULL)
        last = last->_next;
    last->_next = new;
    return true;
}

command_t *queue_pop_front(queue_command_t **q)
{
    queue_command_t *tmp = *q;
    command_t *command = NULL;

    if (!tmp)
        return NULL;
    *q = tmp->_next;
    command = tmp->_command;
    free(tmp);
    return command;
}

void queue_display(queue_command_t *q)
{
    queue_command_t *tmp = q;

    while (tmp != NULL) {
        printf("id: %d, time: %d\n", tmp->_command->_id, tmp->_command->_time);
        tmp = tmp->_next;
    }
}

void queue_destroy(queue_command_t **q)
{
    queue_command_t *tmp = *q;
    queue_command_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->_next;
        free(tmp);
        tmp = next;
    }
    *q = NULL;
}
