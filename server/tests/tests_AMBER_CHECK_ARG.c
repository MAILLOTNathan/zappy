/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tests_AMBER_CHECK_ARG
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "amber_check_arg.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(amber_get_flags, test_amber_get_flags)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100", "-c", "10"};
    int ac = 11;
    cr_assert_eq(amber_get_flags(ac, av, "-p"), 4242);
    cr_assert_eq(amber_get_flags(ac, av, "-x"), 10);
    cr_assert_eq(amber_get_flags(ac, av, "-y"), 10);
    cr_assert_eq(amber_get_flags(ac, av, "-f"), 100);
    cr_assert_eq(amber_get_flags(ac, av, "-c"), 10);
}

Test(amber_get_flags, missing_flag)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100", "-n", "team1", "-c"};
    int ac = 9;
    cr_assert_eq(amber_get_flags(ac, av, "-c"), -1);
}

Test(amber_check_arg, test_amber_check_arg)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100", "-c", "10", "-n", "team1"};
    int ac = 13;
    args_t args = {0};
    cr_assert_eq(amber_check_arg(ac, av, &args), true);
    cr_assert_eq(args.port, 4242);
    cr_assert_eq(args.width, 10);
    cr_assert_eq(args.height, 10);
    cr_assert_eq(args.freq, 100);
    cr_assert_eq(args.clientsNb, 10);
}

Test(amber_check_arg, missing_arg_c)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100", "-n", "team1"};
    int ac = 10;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_arg_f)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-c", "10", "-n", "team1"};
    int ac = 10;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_arg_y)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-f", "100", "-c", "10", "-n", "team1"};
    int ac = 10;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_arg_x)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-y", "10", "-f", "100", "-c", "10", "-n", "team1"};
    int ac = 10;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_arg_p)
{
    char *av[] = {"./zappy_server", "-x", "10", "-y", "10", "-f", "100", "-c", "10", "-n", "team1"};
    int ac = 10;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_flag)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100", "-c", "-n", "team1"};
    int ac = 11;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_get_team_name, test_amber_get_team_name)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-n", "team1", "team2", "team3", "-x", "10", "-y", "10", "-f", "100", "-c", "10"};
    int ac = 15;
    args_t args = {0};
    cr_assert_eq(amber_get_team_name(ac, av, &args), true);
    cr_assert_str_eq(args.teams[0], "team1");
    cr_assert_str_eq(args.teams[1], "team2");
    cr_assert_str_eq(args.teams[2], "team3");
}

Test(amber_get_team_name, missing_team_name)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-n", "-x", "10", "-y", "10", "-f", "100", "-c", "10"};
    int ac = 12;
    args_t args = {0};
    cr_assert_eq(amber_get_team_name(ac, av, &args), false);
}

Test(amber_display_args, test_amber_display_args, .init = redirect_all_stdout)
{
    char *teams[3] = {"team1", "team2", NULL};
    args_t args = {4242, 10, 10, teams, 10, 100};

    amber_display_args(&args);
    // cr_assert_stdout_eq_str("===========Amber arguments===========\nPort: 4242\nWidth: 10\nHeight: 10\nFrequency: 100.000000\nClients per team: 10\n=====================================\n");
}
