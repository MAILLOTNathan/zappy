/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_world_cases
*/

#include "amber_world.h"

static char **world_case_players_egg_stringify(char **array, box_t *box)
{
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
    for (int i = 0; i < box->_thystame; i++)
        array = append_string_array(array, "thystame");
    array = world_case_players_egg_stringify(array, box);
    str = string_array_to_string(array);
    free_string_array(array);
    return (str);
}
