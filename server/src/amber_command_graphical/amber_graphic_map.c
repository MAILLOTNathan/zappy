/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_map
*/

#include "amber_command_graphical.h"


void amber_graphic_msz(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_data, NULL, 0, T_MSZ);
}

void amber_graphic_bct(amber_net_cli_t *client, UNUSED char **arg)
{
    char *str = NULL;

    if (length_string_array(arg) != 3) {
        snprintfizer(client, "sbp bct");
        return;
    }
    str = strdup(arg[1]);
    str = realloc(str, strlen(str) + strlen(arg[2]) + 2);
    strcat(str, " ");
    strcat(str, arg[2]);
    queue_push_back_d(&client->_queue_command, str, 0, T_BCT);
}

void amber_graphic_mct(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 0, T_MCT);
}

void amber_graphic_sgt(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 0, T_SGT);
}

void amber_graphic_sst(amber_net_cli_t *client, char **arg)
{
    if (length_string_array(arg) != 2) {
        snprintfizer(client, "sbp sst");
        return;
    }
    queue_push_back_d(&client->_queue_command, strdup(arg[1]), 0, T_SST);
}
