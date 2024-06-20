/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_graphic_player
*/

#include "amber_command_graphical.h"

void amber_graphic_tna(amber_net_cli_t *client, UNUSED char **arg)
{
    queue_command_t *queue = QUEUE_CAST(client);

    queue_push_back_d(&queue, NULL, 0, T_TNA);
}

void amber_graphic_ppo(amber_net_cli_t *client, char **arg)
{
    queue_command_t *queue = QUEUE_CAST(client);

    if (length_string_array(arg) != 2) {
        snprintfizer(client, "sbp ppo");
        return;
    }
    queue_push_back_d(&queue, strdup(arg[1]), 0, T_PPO);
}

void amber_graphic_plv(amber_net_cli_t *client, char **arg)
{
    queue_command_t *queue = QUEUE_CAST(client);

    if (length_string_array(arg) != 2) {
        snprintfizer(client, "sbp plv");
        return;
    }
    queue_push_back_d(&queue, strdup(arg[1]), 0, T_PLV);
}

void amber_graphic_pin(amber_net_cli_t *client, char **arg)
{
    queue_command_t *queue = QUEUE_CAST(client);

    if (length_string_array(arg) != 2) {
        snprintfizer(client, "sbp pin");
        return;
    }
    queue_push_back_d(&queue, strdup(arg[1]), 0, T_PIN);
}
