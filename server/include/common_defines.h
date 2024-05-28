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
 * @enum direction_s
 * @brief Represents the possible directions.
 */
typedef enum direction_s {
    UP = 1,     /**< Up direction */
    RIGHT = 2,  /**< Right direction */
    DOWN = 3,   /**< Down direction */
    LEFT = 4    /**< Left direction */
} direction_t;

#endif /* !COMMONDEFINES_H_ */
