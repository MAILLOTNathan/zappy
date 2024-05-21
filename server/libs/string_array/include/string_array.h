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
[[__nodiscard__]] char **append_string_array(char **array, char *string);
[[__nodiscard__]] char **pop_back_string_array(char **array);
[[__nodiscard__]] char **pop_front_string_array(char **array);
[[__nodiscard__]] char **prepend_string_array(char **array, char *string);
[[__nodiscard__]] char **insert_string_array(char **arr, char *str, int idx);
[[__nodiscard__]] char **remove_string_array(char **array, int index);
bool contains_string_array(char **array, char *string);
[[__nodiscard__]] char *string_array_to_string(char **array);
[[__nodiscard__]] char **string_to_string_array_separator(char *str, char sep);
[[__nodiscard__]] char **string_to_string_array(char *string);

#endif /* !STRING_ARRAY_H_ */
