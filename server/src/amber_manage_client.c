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
#include "amber_command_graphical.h"

void *amber_create_client(va_list *ap)
{
    amber_client_t *client = calloc(1, sizeof(amber_client_t));

    if (!client)
        return NULL;
    client->_buffer = NULL;
    client->_queue_command = NULL;
    client->_tcp._fd = va_arg(*ap, int);
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

static void choose_handler(amber_world_t *world, amber_serv_t *server,
    amber_client_t *client, char *cmd)
{
    char **arg = string_to_string_array(cmd);

    if (arg == NULL)
        return;
    if (client->_is_graphical)
        amber_manage_command_grahical(client, arg);
    else
        amber_manage_command_ai(world, server, client, arg);
    free_string_array(arg);
}

static void eval_command(amber_world_t *world, amber_serv_t *server,
    amber_client_t *client, char *buffer)
{
    char *match = NULL;
    char *cmd = NULL;

    if (client->_buffer == NULL)
        client->_buffer = strdup(buffer);
    else {
        client->_buffer = realloc(client->_buffer,
            strlen(client->_buffer) + 1024 + 1);
        strcat(client->_buffer, buffer);
    }
    do {
        match = strstr(client->_buffer, "\n");
        if (match == NULL)
            break;
        cmd = strndup(client->_buffer, match - client->_buffer);
        memmove(client->_buffer, match + 1, strlen(match));
        client->_buffer[strlen(client->_buffer)] = '\0';
        choose_handler(world, server, client, cmd);
        free(cmd);
    } while (match);
}

void amber_manage_client_read(amber_world_t *world, amber_serv_t *server,
    amber_client_t *client, list_t *clients)
{
    char buffer[1024] = {0};
    int valread = read(client->_tcp._fd, buffer, 1024);

    if (valread == 0) {
        printf("[AMBER INFO] Client disconnected\n");
        remove_node(&clients, list_find_node(
        clients, client, cmp), true);
        fflush(stdout);
        return;
    }
    eval_command(world, server, client, buffer);
}

int amber_get_nbr_clients_by_team(amber_serv_t *server, char *team)
{
    linked_list_t *tmp = server->_clients->nodes;
    int count = 0;

    while (tmp) {
        if (((amber_client_t *)tmp->data)->_team_name == NULL) {
            tmp = tmp->next;
            continue;
        }
        if (!strcmp(((amber_client_t *)tmp->data)->_team_name, team))
            count++;
        tmp = tmp->next;
    }
    return count;
}

amber_client_t *amber_get_client_by_id(list_t *clients, int id)
{
    linked_list_t *tmp = clients->nodes;

    while (tmp) {
        if (((amber_client_t *)tmp->data)->_id == id)
            return (amber_client_t *)tmp->data;
        tmp = tmp->next;
    }
    return NULL;
}
