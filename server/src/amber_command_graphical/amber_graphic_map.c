/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_map
*/

#include "amber_command_graphical.h"


void amber_graphic_msz(amber_client_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 0, T_MSZ);
}

void amber_graphic_bct(amber_client_t *client, UNUSED char **arg)
{
    char *str = NULL;

    if (length_string_array(arg) != 3) {
        dprintf(client->_tcp._fd, "sbp\n");
        return;
    }
    str = strdup(arg[1]);
    str = realloc(str, strlen(str) + strlen(arg[2]) + 2);
    strcat(str, " ");
    strcat(str, arg[2]);
    queue_push_back_d(&client->_queue_command, str, 0, T_BCT);
}

void amber_graphic_mct(amber_client_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 0, T_MCT);
}

void amber_graphic_sgt(amber_client_t *client, UNUSED char **arg)
{
    queue_push_back_d(&client->_queue_command, NULL, 0, T_SGT);
}

void amber_graphic_sst(amber_client_t *client, char **arg)
{
    if (length_string_array(arg) != 2) {
        dprintf(client->_tcp._fd, "sbp\n");
        return;
    }
    queue_push_back_d(&client->_queue_command, strdup(arg[1]), 0, T_SST);
}
