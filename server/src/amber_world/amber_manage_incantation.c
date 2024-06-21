/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_incantation
*/

#include "amber_manage_incantation.h"
#include "amber_logic.h"


info_incantation_t *amber_init_info_incantation(amber_trantor_t *trantor)
{
    info_incantation_t *info = malloc(sizeof(info_incantation_t));

    if (info == NULL)
        return NULL;
    info->_x = trantor->_x;
    info->_y = trantor->_y;
    info->_level = trantor->_level;
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

void amber_add_player_to_incantation(info_incantation_t *info,
    amber_net_cli_t *client)
{
    amber_trantor_t *trantor = TRANTOR(client);

    send_cli_msg(client, "Elevation underway");
    info->_ids = realloc(info->_ids, sizeof(amber_net_cli_t *) *
        (info->_nb_players + 1));
    info->_ids[info->_nb_players] = client;
    info->_nb_players++;
    trantor->_is_incantating = true;
}

static bool check_if_player_in_incantation(info_incantation_t *info,
    amber_net_cli_t *client)
{
    for (int i = 0; i < info->_nb_players; i++) {
        if (info->_ids[i] == client) {
            info->_ids[i] = NULL;
            info->_nb_players--;
            return true;
        }
    }
    return false;
}

void amber_remove_player_from_incantation(list_t *_incantation_grp,
    amber_net_cli_t *client)
{
    linked_list_t *tmp = _incantation_grp->nodes;
    info_incantation_t *info = NULL;

    for (; tmp; tmp = tmp->next) {
        info = (info_incantation_t *)tmp->data;
        if (check_if_player_in_incantation(info, client)) {
            break;
        }
    }
}
