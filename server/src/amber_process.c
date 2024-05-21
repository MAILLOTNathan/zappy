/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_listening
*/

#include "amber_process.h"
#include "amber_manage_client.h"

void amber_waiting_select(amber_serv_t *server)
{
    struct timeval tv = {0, FRAME};

    
    if (select(FD_SETSIZE, &server->_readfds, NULL, NULL, &tv) == -1) {
        perror("select");
        server->_is_running = false;
    }
}

void amber_init_fd(amber_serv_t *server)
{
    linked_list_t *tmp = server->_clients->nodes;

    FD_ZERO(&server->_readfds);
    FD_SET(server->_tcp._fd, &server->_readfds);
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
    if (!contains_string_array(teams_name, team_name)) {
        free(team_name);
        return NULL;
    }
    return team_name;
}

void amber_accept_client(amber_serv_t *server)
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
    printf("[AMBER INFO] New client connected\n");
    dprintf(new_fd, "WELCOME\n");
    team_name = get_team_name(server->_teams_name, new_fd);
    if (!team_name) {
        dprintf(new_fd, "ko\n");
        close(new_fd);
    } else {
        push_front_list(server->_clients, new_fd, team_name);
        dprintf(new_fd, "10 10\n");
    }
}

void amber_manage_client(amber_serv_t *server)
{
    linked_list_t *node = server->_clients->nodes;
    linked_list_t *ref = server->_clients->nodes;
    int len = list_len(server->_clients);
    amber_client_t *client = NULL;

    for (int i = 0; i < len; i++) {
        client = CAST(amber_client_t *, node->data);
        ref = node->next;
        if (FD_ISSET(client->_tcp._fd, &server->_readfds))
            amber_manage_client_read(server, client);
        node = ref;
    }
}

void amber_listening(amber_serv_t *server)
{
    while (server->_is_running) {
        amber_init_fd(server);
        amber_waiting_select(server);
        if (FD_ISSET(server->_tcp._fd, &server->_readfds))
            amber_accept_client(server);
        amber_manage_client(server);
    }
}
