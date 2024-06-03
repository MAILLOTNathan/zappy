/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_clock
*/

#include "amber_clock.h"

unsigned long get_time_in_microseconds(void)
{
    struct timeval time;
    unsigned long time_in_microseconds;

    gettimeofday(&time, NULL);
    time_in_microseconds = (time.tv_sec * 1000000) + time.tv_usec;
    return time_in_microseconds;
}

unsigned long get_new_time_in_microseconds(double ref)
{
    unsigned long time_in_microseconds = get_time_in_microseconds();
    unsigned long time_to_add = (unsigned long)(ref * 1000000);

    time_in_microseconds += time_to_add;
    return time_in_microseconds;
}
