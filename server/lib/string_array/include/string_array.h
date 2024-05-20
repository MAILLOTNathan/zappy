/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** string_array
*/

#ifndef STRING_ARRAY_H_
#define STRING_ARRAY_H_

    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>

void free_string_array(char **array);
int length_string_array(char **array);
char **append_string_array(char **array, char *string);
char **pop_back_string_array(char **array);
char **pop_front_string_array(char **array);
char **prepend_string_array(char **array, char *string);
char **insert_string_array(char **array, char *string, int index);
char **remove_string_array(char **array, int index);
bool contains_string_array(char **array, char *string);
char *string_array_to_string(char **array);
char **string_to_string_array_separator(char *string, char sep);
char **string_to_string_array(char *string);

#endif /* !STRING_ARRAY_H_ */
