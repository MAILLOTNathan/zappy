/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_incantation
*/

#include "amber_manage_incantation.h"

info_incantation_t *amber_init_info_incantation(amber_client_t *client)
{
    info_incantation_t *info = malloc(sizeof(info_incantation_t));

    if (info == NULL)
        return NULL;
    info->_x = client->_x;
    info->_y = client->_y;
    info->_level = client->_level;
    info->_nb_players = 0;
    info->_ids = NULL;
    return info;
}

void *amber_create_incantation_grp(va_list *ap)
{
    return va_arg(*ap, info_incantation_t *);
}

void amber_destroy_incantation_grp(void *data)
{
    info_incantation_t *info = (info_incantation_t *)data;

    free(info->_ids);
    free(info);
}
