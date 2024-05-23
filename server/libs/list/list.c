/*
** EPITECH PROJECT, 2024
** mini_http_server
** File description:
** list
*/

#include "list.h"
#include <stdio.h>


void destroy_list(list_t **l)
{
    if (*l == NULL)
        return;
    destroy_node(&(*l)->nodes, (*l)->destructor);
    free(*l);
    *l = NULL;
}

bool push_front_list(list_t *l, ...)
{
    va_list ap;
    bool result;

    va_start(ap, l);
    result = push_front_node(&l->nodes, l->create, &ap);
    va_end(ap);
    return result;
}

bool push_back_list(list_t *l, ...)
{
    va_list ap;
    bool result;

    va_start(ap, l);
    result = push_back_node(&l->nodes, l->create, &ap);
    va_end(ap);
    return result;
}

bool remove_node(list_t **l, linked_list_t *index, bool free_data)
{
    if (index == NULL)
        return false;
    if (index->prev)
        index->prev->next = index->next;
    if (index->next)
        index->next->prev = index->prev;
    if (index == (*l)->nodes)
        (*l)->nodes = index->next;
    if (free_data)
        (*l)->destructor(index->data);
    free(index);
    index = NULL;
    return true;
}

list_t *create_list(constructor_t constructor, destructor_t destructor)
{
    list_t *l = malloc(sizeof(list_t));

    if (!l)
        return NULL;
    l->nodes = NULL;
    l->create = constructor;
    l->destructor = destructor;
    return l;
}
