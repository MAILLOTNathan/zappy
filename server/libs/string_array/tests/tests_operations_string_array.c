/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_operations_string_array
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "string_array.h"

Test(string_array, insert_string_array_OK)
{
    char **array = string_to_string_array("Hello world!");

    array = insert_string_array(array, "John", 1);

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "John");
    cr_assert_str_eq(array[2], "world!");
    cr_assert_eq(array[3], NULL);
}

Test(string_array, insert_string_array_KO_negative)
{
    char **array = string_to_string_array("Hello world!");

    array = insert_string_array(array, "John", -1);

    cr_assert_eq(array, NULL);
}

Test(string_array, insert_string_array_KO_sup)
{
    char **array = string_to_string_array("Hello world!");

    array = insert_string_array(array, "John", 4);

        cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "world!");
    cr_assert_str_eq(array[2], "John");
}

Test(string_array, remove_string_array_OK)
{
    char **array = string_to_string_array("Hello world!");

    array = remove_string_array(array, 1);

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_eq(array[1], NULL);
}

Test(string_array, remove_string_array_OK_middle)
{
    char **array = string_to_string_array("Hello John world!");

    array = remove_string_array(array, 1);

    cr_assert_str_eq(array[0], "Hello");
    cr_assert_str_eq(array[1], "world!");
    cr_assert_eq(array[2], NULL);
}


Test(string_array, remove_string_array_KO)
{
    char **array = string_to_string_array("Hello world!");

    array = remove_string_array(array, -2);

    cr_assert_eq(array, NULL);
}
