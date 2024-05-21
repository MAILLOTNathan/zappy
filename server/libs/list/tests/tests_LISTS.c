/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_LISTS
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

Test(list, create_list)
{
    list_t *list = create_list(NULL, NULL);

    cr_assert_not_null(list);
    cr_assert_null(list->nodes);
    destroy_list(&list);
}

Test(list, push_front_list)
{
    list_t *list = create_list(&create_int, &destroy_int);

    cr_assert_eq(push_front_list(list, 42), true);
    cr_assert_eq(*(int *)list->nodes->data, 42);
    cr_assert_eq(push_front_list(list, 84), true);
    cr_assert_eq(*(int *)list->nodes->data, 84);
    cr_assert_eq(*(int *)list->nodes->next->data, 42);
    destroy_list(&list);
}

Test(list, push_back_list)
{
    list_t *list = create_list(&create_int, &destroy_int);

    cr_assert_eq(push_back_list(list, 42), true);
    cr_assert_eq(*(int *)list->nodes->data, 42);
    cr_assert_eq(push_back_list(list, 84), true);
    cr_assert_eq(*(int *)list->nodes->data, 42);
    cr_assert_eq(*(int *)list->nodes->next->data, 84);
    destroy_list(&list);
}

Test(list, remove_node)
{
    list_t *list = create_list(&create_int, &destroy_int);

    push_back_list(list, 42);
    push_back_list(list, 84);
    cr_assert_eq(remove_node(&list, list->nodes->next, true), true);
    cr_assert_eq(*(int *)list->nodes->data, 42);
    cr_assert_eq(remove_node(&list, list->nodes, true), true);
    cr_assert_null(list->nodes);
    destroy_list(&list);
}

Test(list, remove_first_node)
{
    list_t *list = create_list(&create_int, &destroy_int);

    push_back_list(list, 42);
    push_back_list(list, 84);
    cr_assert_eq(remove_node(&list, list->nodes, true), true);
    cr_assert_eq(*(int *)list->nodes->data, 84);
    destroy_list(&list);
}

Test(list, destroy_list)
{
    list_t *list = create_list(&create_int, &destroy_int);

    push_back_list(list, 42);
    push_back_list(list, 84);
    destroy_list(&list);
    cr_assert_null(list);
}

Test(list, destroy_list_null)
{
    list_t *list = NULL;

    destroy_list(&list);
    cr_assert_null(list);
}


Test(list, remove_node_null)
{
    list_t *list = NULL;

    cr_assert_eq(remove_node(&list, NULL, true), false);
}

Test(list, create_list_null_malloc)
{
    list_t *list = create_list(&create_int, &destroy_int);

    cr_assert_not_null(list);
    cr_assert_null(list->nodes);
    destroy_list(&list);
}


