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
    for ( int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
    array = NULL;
}

int length_string_array(char **array)
{
    int i = 0;

    if (array == NULL)
        return 0;
    for (; array[i] != NULL; i++);
    return i;
}

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
    free(string);
    return new_array;
}

char **pop_back_string_array(char **array)
{
    int len = length_string_array(array);
    char **new_array = malloc(sizeof(char *) * len);

    if (new_array == NULL) {
        free_string_array(array);
        exit(84);
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
        exit(84);
        return NULL;
    }
    for (int i = 0; i < len - 1; i++)
        new_array[i] = strdup(array[i + 1]);
    array[len] = NULL;
    free_string_array(array);
    return new_array;
}

char **prepend_string_array(char **array, char *string)
{
    int len = length_string_array(array);
    char **new_array = malloc(sizeof(char *) * (len + 2));

    if (new_array == NULL) {
        free_string_array(array);
        exit(84);
        return NULL;
    }
    new_array[0] = strdup(string);
    for ( int i = 0; i < len; i++)
        new_array[i + 1] = strdup(array[i]);
    new_array[len + 1] = NULL;
    free_string_array(array);
    free(string);
    return new_array;
}

char **insert_string_array(char **array, char *string, int index)
{
    int len = length_string_array(array);
    char **new_array = malloc(sizeof(char *) * (len + 2));

    if (new_array == NULL) {
        free_string_array(array);
        exit(84);
        return NULL;
    }
    for (int i = 0; i < index; i++)
        new_array[i] = strdup(array[i]);
    new_array[index] = strdup(string);
    for (int i = index; i < len; i++)
        new_array[i + 1] = strdup(array[i]);
    new_array[len + 1] = NULL;
    free_string_array(array);
    free(string);
    return new_array;
}

char **remove_string_array(char **array, int index)
{
    int len = length_string_array(array);
    char **new_array = malloc(sizeof(char *) * (len));

    if (new_array == NULL) {
        free_string_array(array);
        exit(84);
        return NULL;
    }
    for (int i = 0; i < index; i++)
        new_array[i] = strdup(array[i]);
    for (int i = index; i < len - 1; i++)
        new_array[i] = strdup(array[i + 1]);
    new_array[len] = NULL;
    free_string_array(array);
    return new_array;
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

char *string_array_to_string(char **array)
{
    int len = 0;
    char *string = NULL;

    if (array == NULL)
        return NULL;
    for (int i = 0; array[i] != NULL; i++)
        len += strlen(array[i]) + 1;
    string = malloc(sizeof(char) * len);
    if (string == NULL) {
        free_string_array(array);
        exit(84);
        return NULL;
    }
    for (int i = 0; array[i] != NULL; i++) {
        strcat(string, array[i]);
        if (array[i + 1] != NULL)
            strcat(string, " ");
    }
    free_string_array(array);
    return string;
}

char *get_string_to_sep(char *string, char sep)
{
    int len = 0;

    for (; string[len] != 0 && string[len] != sep; len++);
    return strndup(string, len);
}

char **string_to_string_array_separator(char *string, char sep)
{
    char **arr = NULL;
    char *tmp = NULL;

    for (int i = 0; string[i] != 0; i++) {
        while (string[i] == sep)
            i++;
        if (string[i] != 0) {
            tmp = get_string_to_sep(string + i, sep);
            arr = append_string_array(arr, tmp);
        }
    }
    return arr;
}

char **string_to_string_array(char *string)
{
    return string_to_string_array_separator(string, ' ');
}
