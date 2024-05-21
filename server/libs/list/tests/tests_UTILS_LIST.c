/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_UTILS_LIST
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "list.h"

static void *create_int(va_list *ap)
{
    int *ptr = malloc(sizeof(int));

    *ptr = va_arg(*ap, int);
    return ptr;
}

static void destroy_int(void *data)
{
    free(data);
}

Test(list, list_len)
{
    list_t *list = create_list(&create_int, &destroy_int);

    cr_assert_eq(list_len(list), 0);
    cr_assert_eq(push_back_list(list, 42), true);
    cr_assert_eq(list_len(list), 1);
    cr_assert_eq(push_back_list(list, 84), true);
    cr_assert_eq(list_len(list), 2);
    destroy_list(&list);
}

static bool cmp_int(void *a, void *b)
{
    return *(int *)a == *(int *)b;
}

Test(list, list_find_node)
{
    list_t *list = create_list(&create_int, &destroy_int);

    int a = 42;
    int b = 84;

    cr_assert_eq(list_find_node(list, &a, &cmp_int), NULL);
    cr_assert_eq(push_back_list(list, 42), true);
    cr_assert_eq(list_find_node(list, &a, &cmp_int), list->nodes);
    cr_assert_eq(list_find_node(list, &b, &cmp_int), NULL);
    cr_assert_eq(push_back_list(list, 84), true);
    cr_assert_eq(list_find_node(list, &a, &cmp_int), list->nodes);
    cr_assert_eq(list_find_node(list, &b, &cmp_int), list->nodes->next);
    destroy_list(&list);
}


