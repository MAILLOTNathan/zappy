/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** commonDefines
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

#endif /* !COMMONDEFINES_H_ */
