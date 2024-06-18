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
    client->_is_graphical = va_arg(*ap, int);
    client->_is_error = false;
    client->_team_name = NULL;
    client->_direction = UP;
    client->_x = 0;
    client->_y = 0;
    client->_level = 1;
    client->_inventory = NULL;
    client->_is_incantating = false;
    client->_clock_food = 0;
    client->_ellapsed_time = 0;
    client->_id = 0;
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
    if (tmp->_queue_command)
        queue_destroy(&tmp->_queue_command);
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
        amber_manage_command_graphical(client, arg);
    else
        amber_manage_command_ai(world, server, client, arg);
    free_string_array(arg);
}

static void eval_command(amber_world_t *world, amber_serv_t *server,
    amber_client_t *client, char *buffer)
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
    amber_client_t *client, list_t *clients)
{
    char buffer[1025] = {0};
    int valread = read(client->_tcp._fd, buffer, 1024);

    buffer[valread] = '\0';
    if (valread != 0)
        eval_command(world, server, client, buffer);
    if (valread == 0 || client->_is_error) {
        if (client->_team_name != NULL) {
            world->_case[client->_y][client->_x]._players--;
            amber_event_pdi(client, server->_graphic_clients);
        }
        printf("[AMBER INFO] Client %d died (lost connection)\n",
            client->_tcp._fd);
        remove_node(&clients, list_find_node(
        clients, client, cmp), true);
        fflush(stdout);
        return;
    }
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
