/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** operations_string_array
*/

#include "string_array.h"

char **insert_string_array(char **array, char *string, int index)
{
    int len = length_string_array(array);
    char **new_array = NULL;

    if (index < 0)
        return NULL;
    index = index > len ? len + 1 : index;
    new_array = malloc(sizeof(char *) * (len + 2));
    if (new_array == NULL) {
        free_string_array(array);
        return NULL;
    }
    for (int i = 0; i < index; i++)
        new_array[i] = strdup(array[i]);
    new_array[index] = strdup(string);
    for (int i = index; i < len; i++)
        new_array[i + 1] = strdup(array[i]);
    new_array[len + 1] = NULL;
    free_string_array(array);
    return new_array;
}

char **remove_string_array(char **array, int index)
{
    int len = length_string_array(array);
    char **new_array = NULL;

    if (index < 0 || index >= len)
        return NULL;
    new_array = malloc(sizeof(char *) * len);
    if (new_array == NULL) {
        free_string_array(array);
        return NULL;
    }
    for (int i = 0; i < index; i++)
        new_array[i] = strdup(array[i]);
    for (int i = index; i < len - 1; i++)
        new_array[i] = strdup(array[i + 1]);
    new_array[len - 1] = NULL;
    free_string_array(array);
    return new_array;
}
