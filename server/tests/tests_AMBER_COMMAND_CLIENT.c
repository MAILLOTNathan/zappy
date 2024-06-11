/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_COMMAND_CLIENT
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "amber_command_server.h"

Test(amber_serv_clients, test_amber_serv_clients)
{
    char *teams[] = {"team1", "team2"};
    args_t args = {._width = 10, ._height = 10, ._freq = 1, ._port = 1234,
        ._teams = teams, ._clientsNb = 2};
    amber_serv_t *server = amber_create_server(&args);
    amber_world_t *world = amber_create_world(&args);

    push_back_list(server->_clients, 42, world->_eggs->nodes->data);

    amber_serv_clients(server, NULL, NULL);
    amber_serv_clients(server, NULL, NULL);
}