/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** string_array
*/

#include "string_array.h"

void free_string_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

int length_string_array(char **array)
{
    int i = 0;

    if (array == NULL)
        return 0;
    for (; array[i] != NULL; i++);
    return i;
}

bool contains_string_array(char **array, char *string)
{
    if (array == NULL)
        return false;
    for (int i = 0; array[i] != NULL; i++)
        if (strcmp(array[i], string) == 0)
            return true;
    return false;
}
