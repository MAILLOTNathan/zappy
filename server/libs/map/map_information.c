/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map_information
*/

#include "map.h"

unsigned int map_get_size(map_t *map)
{
    unsigned int size = 0;

    while (map) {
        size++;
        map = map->next;
    }
    return size;
}

bool map_is_empty(map_t *map)
{
    return map == NULL;
}

void map_dump(map_t *map, key_dump_t key_cmp)
{
    pair_t *pair = NULL;

    while (map) {
        pair = (pair_t *)map->value;
        key_cmp(pair->key, pair->value);
        map = map->next;
    }
}
