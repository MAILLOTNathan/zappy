/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_incantation
*/

#ifndef AMBER_MANAGE_INCANTATION_H_
    #define AMBER_MANAGE_INCANTATION_H_

    #include "amber_init.h"

typedef struct info_incantation_s {
    int _x;
    int _y;
    int _level;
    amber_net_cli_t **_ids;
    int _nb_players;
} info_incantation_t;


info_incantation_t *amber_init_info_incantation(amber_trantor_t *trantor);

void *amber_create_incantation_grp(va_list *ap);

void amber_destroy_incantation_grp(void *data);


void amber_add_player_to_incantation(info_incantation_t *info,
    amber_net_cli_t *client);

void amber_remove_player_from_incantation(list_t *_incantation_grp,
    amber_net_cli_t *client);

#endif /* !AMBER_MANAGE_INCANTATION_H_ */
