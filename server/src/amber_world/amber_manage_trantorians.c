/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** amber_manage_trantorians
*/

#include "amber_world.h"

int amber_cmp_trantorians_by_id(const void *id_1, const void *id_2)
{
    return !(*(int *)id_1 == *(int *)id_2);
}
