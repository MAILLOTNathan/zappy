/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include "commonDefines.h"
#include "amber_check_arg.h"

int main(int ac, char **av)
{
    args_t args = {0};

    if (amber_check_arg(ac, av, &args) == false)
        return 84;
    amber_display_args(&args);
    return 0;
}
