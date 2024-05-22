/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_queue_utils
*/

#include "amber_queue_command.h"

int queue_command_size(queue_command_t *queue)
{
    int size = 0;
    queue_command_t *tmp = queue;

    while (tmp) {
        size++;
        tmp = tmp->_next;
    }
    return size;
}

void queue_display(queue_command_t *q)
{
    queue_command_t *tmp = q;

    while (tmp != NULL) {
        printf("id: %d, time: %d\n", tmp->_command->_id, tmp->_command->_time);
        tmp = tmp->_next;
    }
}
