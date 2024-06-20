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
    amber_net_cli_t *client = calloc(1, sizeof(amber_net_cli_t));

    if (!client)
        return NULL;
    client->_buffer = NULL;
    client->_tcp._fd = va_arg(*ap, int);
    client->_type = va_arg(*ap, client_type_t);
    client->_is_error = false;
    client->_data = NULL;
    client->_id = -1;
    return client;
}

void amber_destroy_client(void *client)
{
    amber_net_cli_t *tmp = (amber_net_cli_t *)client;

    close(tmp->_tcp._fd);
    if (tmp->_buffer)
        free(tmp->_buffer);
    free(tmp);
}

static bool cmp(void *data, void *data_ref)
{
    return (data == data_ref);
}

static void choose_handler(amber_world_t *world, amber_serv_t *server,
    amber_net_cli_t *client, char *cmd)
{
    char **arg = string_to_string_array(cmd);

    if (arg == NULL)
        return;
    if (client->_type == UNKNOWN) {
        amber_init_client(client, server, world, arg);
        return;
    }
    if (client->_type == GRAPHIC)
        amber_manage_command_graphical(client, arg);
    else
        amber_manage_command_ai(world, server, client, arg);
    free_string_array(arg);
}

static void eval_command(amber_world_t *world, amber_serv_t *server,
    amber_net_cli_t *client, char *buffer)
{
    char *match = NULL;
    char *cmd = NULL;

    if (client->_buffer == NULL) {
        client->_buffer = strdup(buffer);
    } else {
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
        choose_handler(world, server, client, cmd);
        free(cmd);
    } while ((match && !client->_is_error));
}

void amber_manage_client_read(amber_world_t *world, amber_serv_t *server,
    amber_net_cli_t *client, list_t *clients)
{
    char buffer[1025] = {0};
    int valread = read(client->_tcp._fd, buffer, 1024);
    amber_trantor_t *trantor = TRANTOR(client);

    buffer[valread] = '\0';
    if (valread != 0)
        eval_command(world, server, client, buffer);
    if (valread == 0 || client->_is_error) {
        if (client->_type == AI) {
            world->_case[trantor->_y][trantor->_x]._players--;
            amber_event_pdi(client, server->_graphic_clients);
        }
        printf("[AMBER INFO] Client %d died (lost connection)\n",
            client->_tcp._fd);
        remove_node(&clients, list_find_node(clients, client, cmp), true);
        fflush(stdout);
        return;
    }
}

amber_net_cli_t *amber_get_client_by_id(list_t *clients, int id)
{
    linked_list_t *tmp = clients->nodes;
    amber_trantor_t *trantor = NULL;
    amber_net_cli_t *client = NULL;

    for (; tmp; tmp = tmp->next) {
        client = (amber_net_cli_t *)tmp->data;
        if (client->_type != AI)
            continue;
        trantor = TRANTOR(client);
        if (trantor->_id == id)
            return client;
    }
    return NULL;
}
