/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_world_cases
*/

#include "amber_world.h"

static char **world_case_players_egg_stringify(char **array, box_t *box)
{
    for (int i = 0; i < box->_thystame; i++)
        array = append_string_array(array, "thystame");
    for (int i = 0; i < box->_players; i++)
        array = append_string_array(array, "player");
    for (int i = 0; i < box->_eggs; i++)
        array = append_string_array(array, "egg");
    return (array);
}

char *amber_world_case_stringify(box_t *box)
{
    char **array = NULL;
    char *str = NULL;

    for (int i = 0; i < box->_food; i++)
        array = append_string_array(array, "food");
    for (int i = 0; i < box->_linemate; i++)
        array = append_string_array(array, "linemate");
    for (int i = 0; i < box->_deraumere; i++)
        array = append_string_array(array, "deraumere");
    for (int i = 0; i < box->_sibur; i++)
        array = append_string_array(array, "sibur");
    for (int i = 0; i < box->_mendiane; i++)
        array = append_string_array(array, "mendiane");
    for (int i = 0; i < box->_phiras; i++)
        array = append_string_array(array, "phiras");
    array = world_case_players_egg_stringify(array, box);
    str = string_array_to_string(array);
    free_string_array(array);
    return (str);
}

box_t *amber_world_case_init(void)
{
    box_t *box = malloc(sizeof(box_t));

    if (box == NULL)
        return NULL;
    box->_food = 0;
    box->_linemate = 0;
    box->_deraumere = 0;
    box->_sibur = 0;
    box->_mendiane = 0;
    box->_phiras = 0;
    box->_thystame = 0;
    box->_players = 0;
    box->_eggs = 0;
    return box;
}
