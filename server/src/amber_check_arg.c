/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_check_arg
*/

#include "amber_check_arg.h"

// bool amber_get_team_name(int ac, char **av, args_t *args)
// {

//     return false;
// }

double amber_get_flags(int ac, char **av, char *flag)
{
    for (int i = 0; i < ac; i++) {
        if (strcmp(av[i], flag) == 0 && i + 1 < ac) {
            return atof(av[i + 1]);
        }
    }
    printf("Error: flag %s not found\n", flag);
    return -1;
}

bool amber_check_arg(int ac, char **av, args_t *args)
{
    args->port = amber_get_flags(ac, av, "-p");
    args->width = amber_get_flags(ac, av, "-x");
    args->height = amber_get_flags(ac, av, "-y");
    args->freq = amber_get_flags(ac, av, "-f");
    args->clientsNb = amber_get_flags(ac, av, "-c");
    if (args->port == -1 || args->width == -1 || args->height == -1
        || args->freq == -1 || args->clientsNb == -1)
        return false;

    return true;
}

void amber_display_args(args_t *args)
{
    printf("===========Amber arguments===========\n");
    printf("Port: %d\n", args->port);
    printf("Width: %d\n", args->width);
    printf("Height: %d\n", args->height);
    printf("Frequency: %f\n", args->freq);
    printf("Clients per team: %d\n", args->clientsNb);
    printf("=====================================\n");
}

