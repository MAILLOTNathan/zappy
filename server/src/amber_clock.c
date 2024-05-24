/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_clock
*/

#include "amber_clock.h"

unsigned long amber_clock_get_ellapsed_time(amber_clock_t *clock)
{
    return clock->_end - clock->_start;
}

void amber_clock_start(amber_clock_t *clock)
{
    struct timeval start;
    clock->_start = gettimeofday(&start, NULL) * 1000000;
    clock->_end = clock->_start;
}

void amber_clock_restart(amber_clock_t *clock)
{
    amber_clock_start(clock);
}

void amber_clock_stop(amber_clock_t *clock)
{
    struct timeval end;
    clock->_end = gettimeofday(&end, NULL) * 1000000;
}

unsigned long amber_clock_set_time_point(amber_clock_t *clock)
{
    struct timeval end;
    clock->_end = gettimeofday(&end, NULL) * 1000000;
    return amber_clock_get_ellapsed_time(clock);
}
