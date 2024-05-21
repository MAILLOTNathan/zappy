/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pop_string_array
*/

#include "string_array.h"

char **pop_back_string_array(char **array)
{
    int len = length_string_array(array);
    char **new_array = malloc(sizeof(char *) * len);

    if (new_array == NULL) {
        free_string_array(array);
        return NULL;
    }
    for (int i = 0; i < len - 1; i++)
        new_array[i] = strdup(array[i]);
    array[len] = NULL;
    free_string_array(array);
    return new_array;
}

char **pop_front_string_array(char **array)
{
    int len = length_string_array(array);
    char **new_array = malloc(sizeof(char *) * len);

    if (new_array == NULL) {
        free_string_array(array);
        return NULL;
    }
    for (int i = 0; i < len - 1; i++)
        new_array[i] = strdup(array[i + 1]);
    array[len] = NULL;
    free_string_array(array);
    return new_array;
}
