/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_string_array
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "string_array.h"

Test(string_array, length_string_array_OK)
{
    char **array = string_to_string_array("Hello world!");

    cr_assert_eq(length_string_array(array), 2);
}

Test(string_array, length_string_array_KO)
{
    char **array = NULL;

    cr_assert_eq(length_string_array(array), 0);
}

Test(string_array, contains_string_array_OK)
{
    char **array = string_to_string_array("Hello world!");

    cr_assert_eq(contains_string_array(array, "Hello"), true);
}

Test(string_array, contains_string_array_KO)
{
    char **array = string_to_string_array("Hello world!");

    cr_assert_eq(contains_string_array(array, "John"), false);
}

Test(string_array, contains_string_array_KO_null)
{
    char **array = NULL;

    cr_assert_eq(contains_string_array(array, "John"), false);
}