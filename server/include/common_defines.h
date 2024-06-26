/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** commonDefines
*/

/**
 * @file common_defines.h
 * @brief Contains the definition of the direction_t enum.
 */

#ifndef COMMONDEFINES_H_
    #define COMMONDEFINES_H_

    /**
     * @brief Macro to mark a variable as unused.
     *
     * This macro is used to mark a variable as unused to avoid
     * compiler warnings.
     * It uses the `__attribute__((unused))` attribute to achieve this.
     *
     * Example usage:
     * ```
     * int foo UNUSED;
     * ```
     */
    #define UNUSED __attribute__((unused))

    /**
     * @brief Macro to calculate the minimum of two values.
     *
     * This macro takes two values and returns the smaller of the two.
     *
     * @param a The first value.
     * @param b The second value.
     * @return The smaller of the two values.
     */
    #define MIN(a, b) ((a) < (b) ? (a) : (b))

    /**
     * @brief Macro to calculate the maximum of two values.
     *
     * This macro takes two values and returns the larger of the two.
     *
     * @param a The first value.
     * @param b The second value.
     * @return The larger of the two values.
     */
    #define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @enum direction_s
 * @brief Represents the possible directions.
 */
typedef enum direction_s {
    UP = 1,     /**< Up direction */
    RIGHT,  /**< Right direction */
    DOWN,   /**< Down direction */
    LEFT    /**< Left direction */
} direction_t;

typedef enum client_type_s {
    AI = 1,
    GRAPHIC,
    UNKNOWN
} client_type_t;

#endif /* !COMMONDEFINES_H_ */
