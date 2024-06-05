/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_clock
*/

#ifndef AMBER_CLOCK_H_
    #define AMBER_CLOCK_H_

    #include <sys/time.h>
    #include <stdio.h>

unsigned long get_time_in_microseconds(void);
unsigned long get_new_time_in_microseconds(double ref);

#endif /* !AMBER_CLOCK_H_ */
