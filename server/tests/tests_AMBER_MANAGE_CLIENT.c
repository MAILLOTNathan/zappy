/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_MANAGE_CLIENT
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "amber_manage_client.h"
#include "list.h"
#include "amber_world.h"
#include "amber_manage_command_ai.h"

Test(amber_create_client, test_amber_create_client)
{
    char *teams[] = {"team1", "team2"};
    args_t args = {._width = 10, ._height = 10, ._freq = 1, ._port = 1234,
        ._teams = teams, ._clientsNb = 2};
    amber_world_t *world = amber_create_world(&args);
    amber_serv_t *server = amber_create_server(&args);
    amber_client_t *client = NULL;

    push_back_list(server->_clients, 42, world->_eggs->nodes->data);

    client = server->_clients->nodes->data;
    cr_assert_eq(client->_tcp._fd, 42);
    cr_assert_str_eq(client->_team_name, "team1");
}

Test(amber_destroy_client, test_amber_destroy_client)
{
    char *teams[] = {"team1", "team2"};
    args_t args = {._width = 10, ._height = 10, ._freq = 1, ._port = 1235,
        ._teams = teams, ._clientsNb = 2};
    amber_world_t *world = amber_create_world(&args);
    amber_serv_t *server = amber_create_server(&args);
    amber_client_t *client = NULL;

    push_back_list(server->_clients, 42, world->_eggs->nodes->data);

    client = server->_clients->nodes->data;
    client->_buffer = strdup("test");
    amber_destroy_client(client);
}
