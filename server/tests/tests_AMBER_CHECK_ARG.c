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
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100", "-c"};
    int ac = 9;
    cr_assert_eq(amber_get_flags(ac, av, "-c"), -1);
}

Test(amber_check_arg, test_amber_check_arg)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100", "-c", "10"};
    int ac = 11;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), true);
    cr_assert_eq(args.port, 4242);
    cr_assert_eq(args.width, 10);
    cr_assert_eq(args.height, 10);
    cr_assert_eq(args.freq, 100);
    cr_assert_eq(args.clientsNb, 10);
}

Test(amber_check_arg, missing_arg_c)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100"};
    int ac = 9;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_arg_f)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-c", "10"};
    int ac = 9;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_arg_y)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-f", "100", "-c", "10"};
    int ac = 9;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_arg_x)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-y", "10", "-f", "100", "-c", "10"};
    int ac = 9;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_arg_p)
{
    char *av[] = {"./zappy_server", "-x", "10", "-y", "10", "-f", "100", "-c", "10"};
    int ac = 9;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_check_arg, missing_flag)
{
    char *av[] = {"./zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-f", "100", "-c"};
    int ac = 10;
    args_t args;
    cr_assert_eq(amber_check_arg(ac, av, &args), false);
}

Test(amber_display_args, test_amber_display_args, .init = redirect_all_stdout)
{
    args_t args = {4242, 10, 10, NULL, 10, 100};

    amber_display_args(&args);
    // cr_assert_stdout_eq_str("===========Amber arguments===========\nPort: 4242\nWidth: 10\nHeight: 10\nFrequency: 100.000000\nClients per team: 10\n=====================================\n");
}
