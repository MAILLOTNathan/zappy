/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_conversions_string_array
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "string_array.h"

Test(string_array, string_array_to_string_OK)
{
    char **array = malloc(sizeof(char *) * 3);
    array[0] = strdup("Hello");
    array[1] = strdup("World");
    array[2] = NULL;
    cr_assert_str_eq(string_array_to_string(array), "Hello World");
}

Test(string_array, string_array_to_string_KO)
{
    char **array = NULL;
    cr_assert_eq(string_array_to_string(array), NULL);
}

Test(string_array, string_to_string_array_separator_OK)
{
    char **array = string_to_string_array_separator(" Hello World ", ' ');
    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "World");
    cr_assert_eq(array[2], NULL);
}

Test(string_array, string_to_string_array_separator_KO)
{
    char **array = string_to_string_array_separator(" Hello World ", ',');
    cr_assert_str_eq(array[0], " Hello World ");
    cr_assert_eq(array[1], NULL);
}

Test(string_array, string_to_string_array_OK)
{
    char **array = string_to_string_array(" Hello World ");
    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "World");
    cr_assert_eq(array[2], NULL);
}

Test(string_array, string_to_string_array_KO)
{
    char **array = string_to_string_array(NULL);
    cr_assert_eq(array, NULL);
}
