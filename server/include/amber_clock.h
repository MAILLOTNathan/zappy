/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_clock
*/

#ifndef AMBER_CLOCK_H_
    #define AMBER_CLOCK_H_

    #include <time.h>
    #include <stdio.h>

/**
 * @brief Amber clock structure to measure time intervals.
 */
typedef struct amber_clock_s {
    /**
     * @brief Start time of the interval.
     */
    unsigned long _start;
    /**
     * @brief End time of the interval.
     */
    unsigned long _end;
} amber_clock_t;

/**
 * @brief Starts the timer.
 *
 * @param[in, out] clock The amber clock instance to start.
 */
void amber_clock_start(amber_clock_t *clock);

/**
 * @brief Restarts the timer.
 *
 * @param[in, out] clock The amber clock instance to restart.
 */
void amber_clock_restart(amber_clock_t *clock);

/**
 * @brief Stops the timer.
 *
 * @param[in, out] clock The amber clock instance to stop.
 */
void amber_clock_stop(amber_clock_t *clock);

/**
 * @brief Sets the end time of the interval.
 *
 * @param[in, out] clock The amber clock instance to set the time point.
 * @return The end time of the interval.
 */
unsigned long amber_clock_set_time_point(amber_clock_t *clock);

/**
 * @brief Returns the time elapsed between the start and end times of
 * the interval.
 *
 * @param[in] clock The amber clock instance to get the time elapsed.
 * @return The time elapsed in milliseconds.
 */
unsigned long amber_clock_get_ellapsed_time(amber_clock_t *clock);

#endif /* !AMBER_CLOCK_H_ */
