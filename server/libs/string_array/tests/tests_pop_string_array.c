/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_pop_string_array
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "string_array.h"

Test(string_array, pop_back_string_array_OK)
{
    char **array = string_to_string_array("Hello world!");

    array = pop_back_string_array(array);

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_eq(array[1], NULL);
}

Test(string_array, pop_back_string_array_KO)
{
    char **array = NULL;

    array = pop_back_string_array(array);

    cr_assert_eq(array, NULL);
}

Test(string_array, pop_front_string_array_OK)
{
    char **array = string_to_string_array("Hello world!");

    array = pop_front_string_array(array);

    cr_assert_str_eq(array[0], "world!");
    cr_assert_eq(array[1], NULL);
}

Test(string_array, pop_front_string_array_KO)
{
    char **array = NULL;

    array = pop_front_string_array(array);

    cr_assert_eq(array, NULL);
}
