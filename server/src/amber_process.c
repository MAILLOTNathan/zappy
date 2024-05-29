/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_listening
*/

#include "amber_process.h"
#include "amber_manage_client.h"
#include "amber_command_server.h"
#include "amber_logic.h"
#include "amber_command_graphical.h"

static void amber_waiting_select(amber_serv_t *server)
{
    if (select(FD_SETSIZE, &server->_readfds, NULL, NULL, NULL) == -1) {
        perror("select");
        server->_is_running = false;
    }
}

void amber_init_fd(amber_serv_t *server)
{
    linked_list_t *tmp = server->_clients->nodes;

    FD_ZERO(&server->_readfds);
    FD_SET(server->_tcp._fd, &server->_readfds);
    FD_SET(0, &server->_readfds);
    while (tmp) {
        FD_SET(((amber_client_t *)tmp->data)->_tcp._fd, &server->_readfds);
        tmp = tmp->next;
    }
    tmp = server->_graphic_clients->nodes;
    while (tmp) {
        FD_SET(((amber_client_t *)tmp->data)->_tcp._fd, &server->_readfds);
        tmp = tmp->next;
    }
}

static char *get_team_name(UNUSED char **teams_name, int fd)
{
    char *team_name = NULL;
    int len = 0;

    do {
        team_name = realloc(team_name, len + 2);
        read(fd, team_name + len, 1);
        len++;
    } while (team_name[len - 1] != '\n');
    team_name[len - 1] = '\0';
    printf("[AMBER INFO] Team name received: %s\n", team_name);
    if (!contains_string_array(teams_name, team_name) &&
        strcmp(team_name, "GRAPHIC") != 0){
        free(team_name);
        return NULL;
    }
    return team_name;
}

static void display_info_client_ai(int new_fd, amber_serv_t *server,
    char *team_name, amber_world_t *world)
{
    dprintf(new_fd, "%d\n",
    world->_clientsNb - amber_get_nbr_clients_by_team(server, team_name));
    dprintf(new_fd, "%d %d\n", world->_width, world->_height);
    printf("[AMBER INFO] New client connected\n");
}

static void add_client(amber_serv_t *server, int new_fd, char *team_name,
    amber_world_t *world)
{
    egg_t *egg = NULL;

    team_name = get_team_name(server->_teams_name, new_fd);
    if (!team_name) {
        dprintf(new_fd, "ko\n");
        return (void)close(new_fd);
    }
    if (strcmp(team_name, "GRAPHIC") == 0) {
        push_front_list(server->_graphic_clients, new_fd, NULL, true);
        return (void)printf("[AMBER INFO] New graphic client connected\n");
    }
    egg = amber_get_egg_by_team(world, team_name);
    if (!egg) {
        dprintf(new_fd, "ko\n");
        close(new_fd);
        return;
    }
    push_back_list(server->_clients, new_fd, egg, false);
    display_info_client_ai(new_fd, server, team_name, world);
}

static void amber_accept_client(amber_serv_t *server, amber_world_t *world)
{
    int new_fd;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);
    char *team_name = NULL;

    new_fd = accept(server->_tcp._fd, (struct sockaddr *)&addr, &addrlen);
    if (new_fd == -1) {
        printf("[AMBER ERROR] Accept failed\n");
        return;
    }
    dprintf(new_fd, "WELCOME\n");
    add_client(server, new_fd, team_name, world);
}

void amber_manage_client(amber_world_t *world, amber_serv_t *server,
    list_t *clients)
{
    linked_list_t *node = clients->nodes;
    linked_list_t *ref = clients->nodes;
    int len = list_len(clients);
    amber_client_t *client = NULL;

    for (int i = 0; i < len; i++) {
        client = CAST(amber_client_t *, node->data);
        ref = node->next;
        if (FD_ISSET(client->_tcp._fd, &server->_readfds))
            amber_manage_client_read(world, server, client, clients);
        node = ref;
    }
}

void amber_manage_server_command(amber_serv_t *server, amber_world_t *world)
{
    char *buffer = NULL;
    size_t len = 0;

    getline(&buffer, &len, stdin);
    buffer[strlen(buffer) - 1] = '\0';
    amber_manage_command(server, world, buffer);
}

void amber_listening(amber_serv_t *server, amber_world_t *world)
{
    while (server->_is_running) {
        amber_init_fd(server);
        amber_waiting_select(server);
        if (FD_ISSET(server->_tcp._fd, &server->_readfds))
            amber_accept_client(server, world);
        amber_manage_client(world, server, server->_clients);
        amber_manage_client(world, server, server->_graphic_clients);
        amber_graphic_loop(server, world);
        if (FD_ISSET(0, &server->_readfds))
            amber_manage_server_command(server, world);
        amber_logic_loop(server, world);
    }
}
