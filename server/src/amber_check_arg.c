/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_check_arg
*/

#include "amber_check_arg.h"

static bool add_team_name(args_t *args, char **av, int i, int ac)
{
    for (int j = i; j < ac; j++) {
        if (av[j][0] != '-') {
            args->_teams = append_string_array(args->_teams, strdup(av[j]));
        } else {
            break;
        }
    }
    if (length_string_array(args->_teams) == 0) {
        printf("Error: no team name found\n");
        return false;
    }
    return true;
}

bool amber_get_team_name(int ac, char **av, args_t *args)
{
    for (int i = 0; i < ac; i++) {
        if (strcmp(av[i], "-n") == 0 && i + 1 < ac) {
            return add_team_name(args, av, i + 1, ac);
        }
    }
    printf("Error: flag -n not found\n");
    return false;
}

double amber_get_flags(int ac, char **av, char *flag)
{
    double res = -1;

    for (int i = 0; i < ac; i++) {
        if (res != -1 && strcmp(av[i], flag) == 0) {
            printf("Error: flag %s already found\n", flag);
            return -1;
        }
        if (strcmp(av[i], flag) == 0 && i + 1 < ac) {
            res = atof(av[i + 1]);
        }
    }
    if (res == -1)
        printf("Error: flag %s not found\n", flag);
    return res;
}

bool amber_check_arg(int ac, char **av, args_t *args)
{
    args->_port = amber_get_flags(ac, av, "-p");
    args->_width = amber_get_flags(ac, av, "-x");
    args->_height = amber_get_flags(ac, av, "-y");
    args->_freq = amber_get_flags(ac, av, "-f");
    args->_clientsNb = amber_get_flags(ac, av, "-c");
    if (args->_port == -1 || args->_width == -1 || args->_height == -1
        || args->_freq == -1 || args->_clientsNb == -1)
        return false;
    if (amber_get_team_name(ac, av, args) == false)
        return false;
    return true;
}

void amber_display_args(args_t *args)
{
    printf("===========Amber arguments===========\n");
    printf("Port: %d\n", args->_port);
    printf("Width: %d\n", args->_width);
    printf("Height: %d\n", args->_height);
    printf("Frequency: %f\n", args->_freq);
    printf("Clients per team: %d\n", args->_clientsNb);
    printf("Teams: \n");
    for (int i = 0; args->_teams[i] != NULL; i++)
        printf("- %s\n", args->_teams[i]);
    printf("=====================================\n");
}

