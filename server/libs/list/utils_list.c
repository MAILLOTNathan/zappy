/*
** EPITECH PROJECT, 2024
** B-NWP-400-RUN-4-1-myftp-leo.sautron
** File description:
** utils_list
*/

#include "list.h"

size_t list_len(list_t *l)
{
    size_t len = 0;
    linked_list_t *tmp = l->nodes;

    while (tmp) {
        len++;
        tmp = tmp->next;
    }
    return len;
}

linked_list_t *list_find_node(list_t *l, void *data,
    bool (*cmp)(void *, void *))
{
    linked_list_t *tmp = l->nodes;

    while (tmp) {
        if (cmp(tmp->data, data))
            return tmp;
        LIST_FORWARD(tmp);
    }
    return NULL;
}

linked_list_t *list_find_node_p(list_t *l, void *ref)
{
    linked_list_t *tmp = l->nodes;

    while (tmp) {
        if (ref == tmp->data)
            return tmp;
        LIST_FORWARD(tmp);
    }
    return NULL;
}
