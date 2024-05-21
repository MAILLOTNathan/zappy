/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "common_defines.h"
#include "amber_process.h"
#include "amber_world.h"
#include "amber_clock.h"
#include "signal.h"

amber_serv_t *server;

void handle_sigint(int sig)
{
    (void)sig;
    server->_is_running = false;
    amber_destroy_server(server);
    exit(0);
}

int main(int ac, char **av)
{
    args_t args = {0};
    amber_world_t *world = NULL;

    srand(time(NULL));
    signal(SIGINT, handle_sigint);
    if (amber_check_arg(ac, av, &args) == false)
        return 84;
    amber_display_args(&args);
    server = amber_create_server(&args);
    if (!server)
        return 84;
    world = amber_create_world(args._width, args._height, args._teams);
    if (!world)
        return 84;
    amber_listening(server, world);
    return 0;
}
