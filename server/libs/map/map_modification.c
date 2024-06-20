/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map_modification
*/

#include "map.h"

static bool map_del_elem_at_front(map_t **front_ptr)
{
    map_t *tmp = *front_ptr;

    if (map_is_empty(*front_ptr))
        return false;
    tmp = (*front_ptr)->next;
    free(*front_ptr);
    *front_ptr = tmp;
    return true;
}

static map_t *create_node(void *key, void *value)
{
    map_t *new = malloc(sizeof(map_t));
    pair_t *new_pair = malloc(sizeof(pair_t));

    if (new == NULL || new_pair == NULL)
        return NULL;
    new_pair->key = key;
    new_pair->value = value;
    new->value = new_pair;
    new->next = NULL;
    return new;
}

bool map_add_elem(map_t **map_ptr, void *key, void *value,
    key_comparator_t key_cmp)
{
    map_t *tmp = *map_ptr;

    if (map_is_empty(*map_ptr)) {
        *map_ptr = create_node(key, value);
        return *map_ptr == NULL ? false : true;
    }
    while (tmp != NULL) {
        if (key_cmp(((pair_t *)tmp->value)->key, key) == 0) {
            ((pair_t *)tmp->value)->value = value;
            return true;
        }
        tmp = tmp->next;
    }
    tmp = create_node(key, value);
    tmp->next = *map_ptr;
    *map_ptr = tmp;
    return true;
}

bool map_del_elem(map_t **map_ptr, void *key, key_comparator_t key_cmp)
{
    map_t *tmp = NULL;
    map_t *list = *map_ptr;

    if (map_is_empty(*map_ptr))
        return false;
    if (key_cmp(((pair_t *)list->value)->key, key) == 0) {
        return map_del_elem_at_front(map_ptr);
    }
    while (list->next != NULL) {
        if (key_cmp(((pair_t *)list->next->value)->key, key) == 0) {
            tmp = list->next->next;
            free(list->next);
            list->next = tmp;
            return true;
        }
        list = list->next;
    }
    return false;
}

void map_clear(map_t **map_ptr)
{
    map_t *gree = *map_ptr;

    while (*map_ptr) {
        gree = (*map_ptr)->next;
        free((*map_ptr)->value);
        free(*map_ptr);
        *map_ptr = gree;
    }
}
