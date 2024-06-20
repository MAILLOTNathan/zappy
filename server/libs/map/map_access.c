/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map_access
*/

#include "map.h"

void *map_get_elem(map_t *map, void *key, key_comparator_t key_cmp)
{
    while (map != NULL) {
        if (key_cmp(((pair_t *)map->value)->key, key) == 0)
            return ((pair_t *)map->value)->value;
        map = map->next;
    }
    return NULL;
}
