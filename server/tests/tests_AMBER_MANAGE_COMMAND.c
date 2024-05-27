/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_MANAGE_COMMAND
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "amber_command_server.h"

Test(amber_manage_command, test_amber_manage_command)
{
    char *teams[] = {"team1", "team2"};
    args_t args = {._width = 10, ._height = 10, ._freq = 1, ._port = 1234,
        ._teams = teams, ._clientsNb = 2};
    amber_world_t *world = amber_create_world(&args);
    amber_serv_t *server = amber_create_server(&args);
    char *cmd = strdup("/map");
    char *alt = strdup("nerub");

    amber_manage_command(server, world, cmd);
    amber_manage_command(server, world, alt);
}
