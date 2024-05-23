/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_world_egg
*/

#include "amber_world.h"

void *amber_create_egg(va_list *ap)
{
    egg_t *egg = calloc(1, sizeof(egg_t));

    if (!egg)
        return NULL;
    egg->_x = va_arg(*ap, int);
    egg->_y = va_arg(*ap, int);
    egg->_team = strdup(va_arg(*ap, char *));
    egg->_hatching_time = 0;
    egg->_direction = RAND(4);
    egg->_id = va_arg(*ap, int);
    return egg;
}

void amber_destroy_egg(void *gree)
{
    egg_t *egg = (egg_t *)gree;

    if (!egg)
        return;
    free(egg->_team);
    free(egg);
}

egg_t *amber_get_egg_by_team(amber_world_t *world, char *team)
{
    linked_list_t *tmp = world->_eggs->nodes;
    egg_t *egg = NULL;

    while (tmp) {
        if (!strcmp(((egg_t *)tmp->data)->_team, team)) {
            egg = tmp->data;
            remove_node(&world->_eggs, tmp, false);
            return egg;
        }
        tmp = tmp->next;
    }
    return NULL;
}
