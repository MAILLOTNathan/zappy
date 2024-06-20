/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_check_arg
*/

#include "amber_check_arg.h"

static void default_team_name(args_t *args)
{
    char *team_name = strdup("Team1");

    args->_teams = append_string_array(args->_teams, team_name);
    args->_teams = append_string_array(args->_teams, strdup("Team2"));
    free(team_name);
}

static bool add_team_name(args_t *args, char **av, int i, int ac)
{
    char *team_name = NULL;

    for (int j = i; j < ac; j++) {
        if (av[j][0] != '-') {
            team_name = strdup(av[j]);
            args->_teams = append_string_array(args->_teams, team_name);
            free(team_name);
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
    default_team_name(args);
    return true;
}

double amber_get_flags(int ac, char **av, char *flag, int default_value)
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
    return res == -1 ? default_value : res;
}

static void display_help(int exit_code)
{
    printf(HELP"\n");
    printf("\tport: is the port number (0-65535)\n");
    printf("\twidth: is the width of the world\n");
    printf("\theight: is the height of the world\n");
    printf("\tnameX: is the name of the team X\n");
    printf("\tclientsNb: is the number of authorized clients per team\n");
    printf(HELP_FREQ);
    exit(exit_code);
}

bool amber_check_arg(int ac, char **av, args_t *args)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0){
        display_help(0);
    }
    args->_port = amber_get_flags(ac, av, "-p", 4242);
    args->_width = amber_get_flags(ac, av, "-x", 10);
    args->_height = amber_get_flags(ac, av, "-y", 10);
    args->_freq = amber_get_flags(ac, av, "-f", 100);
    args->_clientsNb = amber_get_flags(ac, av, "-c", 2);
    if (args->_port <= 0 || args->_port > 65535 || args->_width <= 0 ||
        args->_height <= 0 || args->_clientsNb <= 0)
        display_help(84);
    args->_freq = args->_freq == -1 ? 100 : args->_freq;
    if (args->_freq <= 0)
        display_help(84);
    if (amber_get_team_name(ac, av, args) == false)
        display_help(84);
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
