/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** conversions_string_array
*/

#include "string_array.h"

static char *copy_array(char **array, char *str)
{
    int len = 0;

    for (int i = 0; array[i] != NULL; i++) {
        for (int j = 0; array[i][j] != 0; j++) {
            str[len] = array[i][j];
            len++;
        }
        str[len] = array[i + 1] == NULL ? 0 : ' ';
        len++;
    }
    return str;
}

char *string_array_to_string(char **array)
{
    int len = 0;
    char *str = NULL;

    if (array == NULL)
        return NULL;
    for (int i = 0; array[i] != NULL; i++)
        len += strlen(array[i]) + 1;
    str = malloc(sizeof(char) * len);
    if (str == NULL) {
        free_string_array(array);
        return NULL;
    }
    return copy_array(array, str);
}

static char *get_string_to_sep(char *string, char sep)
{
    int len = 0;

    for (; string[len] != 0 && string[len] != sep; len++);
    return strndup(string, len);
}

char **string_to_string_array_separator(char *string, char sep)
{
    char **arr = NULL;
    char *tmp = NULL;

    if (string == NULL)
        return NULL;
    for (int i = 0; string[i] != 0; i++) {
        while (string[i] == sep)
            i++;
        if (string[i] != 0) {
            tmp = get_string_to_sep(string + i, sep);
            tmp[strlen(tmp)] = 0;
            i += strlen(tmp);
            arr = append_string_array(arr, tmp);
        }
        if (string[i] == 0)
            break;
    }
    return arr;
}

char **string_to_string_array(char *string)
{
    return string_to_string_array_separator(string, ' ');
}
