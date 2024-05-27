/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_SERV
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "amber_command_server.h"

Test(amber_serv_map, test_amber_serv_map)
{
    char *teams[] = {"team1", "team2"};
    args_t args = {._width = 10, ._height = 10, ._freq = 1, ._port = 8574,
        ._teams = teams, ._clientsNb = 2};
    amber_world_t *world = amber_create_world(&args);
    amber_serv_t *server = amber_create_server(&args);
    char *cmd[] = {"map", "-v"};
    char *alt[] = {"jnde"};

    amber_serv_map(server, world, cmd);
    amber_serv_map(server, world, alt);
}
