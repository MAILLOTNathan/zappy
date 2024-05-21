/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pend_string_array
*/

#include "string_array.h"

char **append_string_array(char **array, char *string)
{
    int len = length_string_array(array);
    char **new_array = malloc(sizeof(char *) * (len + 2));

    if (new_array == NULL) {
        free_string_array(array);
        exit(84);
        return NULL;
    }
    if (len != 0)
        for (int i = 0; array[i] != NULL; i++)
            new_array[i] = strdup(array[i]);
    new_array[len] = strdup(string);
    new_array[len + 1] = NULL;
    free_string_array(array);
    return new_array;
}

char **prepend_string_array(char **array, char *string)
{
    int len = length_string_array(array);
    char **new_array = malloc(sizeof(char *) * (len + 2));

    if (new_array == NULL) {
        free_string_array(array);
        return NULL;
    }
    new_array[0] = strdup(string);
    for (int i = 0; i < len; i++)
        new_array[i + 1] = strdup(array[i]);
    new_array[len + 1] = NULL;
    free_string_array(array);
    return new_array;
}
