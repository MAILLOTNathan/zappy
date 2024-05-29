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

static void *init_client_ai(amber_client_t *client, egg_t *egg)
{
    client->_team_name = strdup(egg->_team);
    client->_direction = egg->_direction;
    client->_x = egg->_x;
    client->_y = egg->_y;
    client->_level = 1;
    client->_id = egg->_id;
    client->_inventory = amber_world_case_init();
    client->_inventory->_food = 10;
    client->_elapsed_time = 0;
    return client;
}

void *amber_create_client(va_list *ap)
{
    amber_client_t *client = calloc(1, sizeof(amber_client_t));
    egg_t *egg = NULL;

    if (!client)
        return NULL;
    client->_tcp._fd = va_arg(*ap, int);
    egg = va_arg(*ap, egg_t *);
    client->_is_graphical = va_arg(*ap, int);
    client->_buffer = NULL;
    client->_queue_command = NULL;
    if (client->_is_graphical)
        return client;
    init_client_ai(client, egg);
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

static void choose_handler(UNUSED amber_serv_t *server, amber_client_t *client,
    char *cmd)
{
    char **arg = string_to_string_array(cmd);

    if (arg == NULL)
        return;
    if (client->_is_graphical)
        amber_manage_command_grahical(client, arg);
    else
        amber_manage_command_ai(client, arg);
    free_string_array(arg);
}

static void eval_command(amber_serv_t *server, amber_client_t *client,
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
        choose_handler(server, client, cmd);
        free(cmd);
    } while (match);
}

void amber_manage_client_read(amber_serv_t *server, amber_client_t *client,
    list_t *clients)
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
    eval_command(server, client, buffer);
}

int amber_get_nbr_clients_by_team(amber_serv_t *server, char *team)
{
    linked_list_t *tmp = server->_clients->nodes;
    int count = 0;

    while (tmp) {
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
        printf("ID: %d\n", ((amber_client_t *)tmp->data)->_id);
        if (((amber_client_t *)tmp->data)->_id == id)
            return (amber_client_t *)tmp->data;
        tmp = tmp->next;
    }
    return NULL;
}