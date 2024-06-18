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
    amber_client_t **_ids;
    int _nb_players;
} info_incantation_t;


info_incantation_t *amber_init_info_incantation(amber_client_t *client);

void *amber_create_incantation_grp(va_list *ap);

void amber_destroy_incantation_grp(void *data);


#endif /* !AMBER_MANAGE_INCANTATION_H_ */
