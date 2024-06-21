/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** amber_manage_trantorians
*/

#include "amber_world.h"
#include "amber_init.h"

int amber_cmp_trantorians_by_id(const void *id_1, const void *id_2)
{
    return !(*(int *)id_1 == *(int *)id_2);
}

bool amber_check_winner(list_t *clients, amber_trantor_t *trantor)
{
    linked_list_t *tmp = clients->nodes;
    amber_net_cli_t *client = NULL;
    amber_trantor_t *t_tmp = NULL;
    int cpt = 0;

    for (; tmp; tmp = tmp->next) {
        client = (amber_net_cli_t *)tmp->data;
        if (client->_type != AI)
            continue;
        t_tmp = TRANTOR(client);
        if (t_tmp->_id == trantor->_id)
            continue;
        if (t_tmp->_level == 8 &&
            strcmp(t_tmp->_team_name, trantor->_team_name) == 0)
            cpt++;
    }
    return cpt == 5;
}
