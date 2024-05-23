/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_client
*/

#include "amber_manage_client.h"
#include "list.h"
#include "amber_world.h"
#include "amber_manage_command_ai.h"

void *amber_create_client(va_list *ap)
{
    amber_client_t *client = calloc(1, sizeof(amber_client_t));
    egg_t *egg = NULL;

    if (!client)
        return NULL;
    client->_tcp._fd = va_arg(*ap, int);
    egg = va_arg(*ap, egg_t *);
    client->_buffer = NULL;
    client->_team_name = strdup(egg->_team);
    client->_direction = egg->_direction;
    client->_x = egg->_x;
    client->_y = egg->_y;
    client->_level = 1;
    client->_id = egg->_id;
    client->_inventory = amber_world_case_init();
    amber_destroy_egg(egg);
    return client;
}

void amber_destroy_client(void *client)
{
    amber_client_t *tmp = (amber_client_t *)client;

    close(tmp->_tcp._fd);
    if (tmp->_buffer)
        free(tmp->_buffer);
    if (tmp->_team_name)
        free(tmp->_team_name);
    free(tmp);
}

static bool cmp(void *data, void *data_ref)
{
    return (data == data_ref);
}

static void eval_command(UNUSED amber_serv_t *server, amber_client_t *client,
    char *buffer)
{
    char *match = NULL;
    char *cmd = NULL;

    if (client->_buffer == NULL)
        client->_buffer = strdup(buffer);
    else {
        client->_buffer = realloc(client->_buffer,
            strlen(client->_buffer) + strlen(buffer) + 1);
        strcat(client->_buffer, buffer);
    }
    do {
        match = strstr(client->_buffer, "\n");
        if (match == NULL)
            break;
        cmd = strndup(client->_buffer, match - client->_buffer);
        memmove(client->_buffer, match + 1, strlen(match));
        client->_buffer[strlen(client->_buffer)] = '\0';
        amber_manage_command_ai(client, cmd);
        free(cmd);
    } while (match);
}

void amber_manage_client_read(amber_serv_t *server, amber_client_t *client)
{
    char buffer[1024] = {0};
    int valread = read(client->_tcp._fd, buffer, 1024);

    if (valread == 0) {
        printf("[AMBER INFO] Client disconnected\n");
        remove_node(&server->_clients, list_find_node(
        server->_clients, client, cmp), true);
        return;
    }
    eval_command(server, client, buffer);
}
