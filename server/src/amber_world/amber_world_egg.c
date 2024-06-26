/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_world_egg
*/

#include "amber_world.h"

void amber_init_egg(amber_world_t *world)
{
    int id = 0;

    world->_eggs = create_list(amber_create_egg, amber_destroy_egg);
    for (int i = 0; world->_teams_name[i]; i++) {
        for (int j = 0; j < world->_clientsNb; j++) {
            push_back_list(world->_eggs, world, RAND(world->_width),
            RAND(world->_height), world->_teams_name[i], id);
            id++;
        }
    }
    world->_last_egg_id = id;
}

void *amber_create_egg(va_list *ap)
{
    egg_t *egg = calloc(1, sizeof(egg_t));
    amber_world_t *world = va_arg(*ap, amber_world_t *);

    if (!egg)
        return NULL;
    egg->_x = va_arg(*ap, int);
    egg->_y = va_arg(*ap, int);
    egg->_team = strdup(va_arg(*ap, char *));
    egg->_hatching_time = 0;
    egg->_direction = RAND(4) + 1;
    egg->_id = va_arg(*ap, int);
    world->_case[egg->_y][egg->_x]._eggs++;
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
            world->_case[egg->_y][egg->_x]._eggs--;
            world->_case[egg->_y][egg->_x]._players++;
            return egg;
        }
        tmp = tmp->next;
    }
    return NULL;
}

int amber_get_nbr_eggs_by_team(amber_world_t *world, char *team)
{
    linked_list_t *tmp = world->_eggs->nodes;
    int count = 0;

    while (tmp) {
        if (!strcmp(((egg_t *)tmp->data)->_team, team))
            count++;
        tmp = tmp->next;
    }
    return count;
}
