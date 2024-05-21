/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_check_arg
*/

#ifndef AMBER_CHECK_ARG_H_
    #define AMBER_CHECK_ARG_H_


    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "string_array.h"

/**
 * @brief Structure representing the arguments for the program.
 *
 * @param port The port number.
 * @param width The width of the game map.
 * @param height The height of the game map.
 * @param teams The array of team names.
 * @param clientsNb The number of clients per team.
 * @param freq The frequency of game cycles.
 */
typedef struct args_s {
    int _port;           /** The port number. */
    int _width;          /** The width of the game map. */
    int _height;         /** The height of the game map. */
    char **_teams;       /** The array of team names. */
    int _clientsNb;      /** The number of clients per team. */
    double _freq;           /** The frequency of game cycles. */
} args_t;


/**
 * @brief Checks the command line arguments for the Amber application.
 *
 * This function takes the command line arguments and checks if they are valid
 * for the Amber application.
 *
 * @param ac The number of command line arguments.
 * @param av An array of strings representing the command line arguments.
 * @param args A pointer to a structure that will store the parsed arguments.
 * @return true if the arguments are valid, false otherwise.
 */
bool amber_check_arg(int ac, char **av, args_t *args);


/**
 * @brief Retrieves the value of a specific flag from the command
 * line arguments.
 *
 * This function searches through the command line arguments to find
 * the specified flag and returns its value.
 *
 * @param ac The number of command line arguments.
 * @param av An array of strings representing the command line arguments.
 * @param flag The flag to search for.
 * @return The value of the specified flag, or NULL if the flag is not found.
 */
double amber_get_flags(int ac, char **av, char *flag);

/**
 * Displays the arguments passed to the program.
 *
 * @param args The arguments structure containing the program arguments.
 */
void amber_display_args(args_t *args);

/**
 * @brief Retrieves the team name from the command line arguments.
 *
 * This function parses the command line arguments and retrieves the team name.
 *
 * @param ac The number of command line arguments.
 * @param av The array of command line arguments.
 * @param args The structure to store the parsed arguments.
 *
 * @return true if the team name was successfully retrieved, false otherwise.
 */
bool amber_get_team_name(int ac, char **av, args_t *args);


#endif /* !AMBER_CHECK_ARG_H_ */
