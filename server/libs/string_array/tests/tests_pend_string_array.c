/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_pend_string_array
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "string_array.h"

Test(string_array, append_string_array_OK)
{
    char **array = string_to_string_array("Hello world!");

    array = append_string_array(array, "John");

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "world!");
    cr_assert_str_eq(array[2], "John");
    cr_assert_eq(array[3], NULL);
}

Test(string_array, append_string_array_OK_empty)
{
    char **array = NULL;

    array = append_string_array(array, "John");

    cr_assert_str_eq(array[0], "John");
    cr_assert_eq(array[1], NULL);
}

Test(string_array, prepend_string_array_OK)
{
    char **array = string_to_string_array("Hello world!");

    array = prepend_string_array(array, "John");

    cr_assert_str_eq(array[0], "John");
    cr_assert_str_eq(array[1], "Hello");
    cr_assert_str_eq(array[2], "world!");
    cr_assert_eq(array[3], NULL);
}

Test(string_array, prepend_string_array_OK_empty)
{
    char **array = NULL;

    array = prepend_string_array(array, "John");

    cr_assert_str_eq(array[0], "John");
    cr_assert_eq(array[1], NULL);
}
