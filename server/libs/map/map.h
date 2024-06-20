/*
** EPITECH PROJECT, 2024
** Paradigms Seminar
** File description:
** Exercise 07
*/

#pragma once

    #include <stdlib.h>
    #include <stdbool.h>

/* Types */

typedef struct pair {
    void *key;
    void *value;
} pair_t;

typedef struct map_s {
    void *value;
    struct map_s *next;
} map_t;

typedef int (*key_comparator_t)(const void *first_key, const void *second_key);
typedef void (*key_dump_t)(const void *key, const void *value);

/* Informations */

unsigned int map_get_size(map_t *map);
bool map_is_empty(map_t *map);
void map_dump(map_t *map, key_dump_t key_cmp);

/* Modification */

bool map_add_elem(map_t **map_ptr, void *key, void *value,
    key_comparator_t key_cmp);
bool map_del_elem(map_t **map_ptr, void *key, key_comparator_t key_cmp);
void map_clear(map_t **map_ptr);

/* Access */

void *map_get_elem(map_t *map, void *key, key_comparator_t key_cmp);
