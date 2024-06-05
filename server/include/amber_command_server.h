/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_server
*/

#ifndef AMBER_COMMAND_SERVER_H_
    #define AMBER_COMMAND_SERVER_H_

    #include "amber_world.h"
    #include "amber_init.h"
    #include "string_array.h"

/**
 * @brief Handles the clients connected to the Amber server.
 *
 * This function is responsible for handling the clients
 * connected to the Amber server.
 * It takes in a pointer to the `amber_serv_t` server structure,
 * a pointer to the `amber_world_t` world structure,
 * and a character buffer.
 *
 * @param server A pointer to the `amber_serv_t` server structure.
 * @param world A pointer to the `amber_world_t` world structure.
 * @param buffer A character buffer.
 */
void amber_serv_clients(amber_serv_t *server, amber_world_t *world,
    char **cmd);

/**
 * @brief Manages a command received by the Amber server.
 *
 * This function is responsible for processing a command received
 * by the Amber server.
 * It takes a pointer to the server structure, a pointer
 * to the world structure, and
 * a buffer containing the command as parameters.
 *
 * @param server A pointer to the Amber server structure.
 * @param world A pointer to the Amber world structure.
 * @param buffer A pointer to the buffer containing the command.
 */
void amber_manage_command(amber_serv_t *server, amber_world_t *world,
    char *buffer);

/**
 * @brief Maps the given command to the corresponding function
 * in the Amber server.
 *
 * This function is responsible for mapping the given command
 * to the corresponding
 * function in the Amber server. It takes a pointer to the server structure,
 * a pointer
 * to the world structure, and a double pointer to the command string
 * as parameters.
 *
 * @param server A pointer to the Amber server structure.
 * @param world A pointer to the Amber world structure.
 * @param cmd A double pointer to the command string.
 */
void amber_serv_map(amber_serv_t *server, amber_world_t *world, char **cmd);

/**
 * @brief Executes the amber_serv_tp command on the specified server.
 *
 * This function is responsible for executing the amber_serv_tp command
 * on the given server.
 * It takes a pointer to the server structure, a pointer to the world
 * structure, and a double pointer to the command string.
 *
 * @param server A pointer to the amber_serv_t structure representing
 * the server.
 * @param world A pointer to the amber_world_t structure representing
 * the world.
 * @param cmd A double pointer to the command string.
 */
void amber_serv_tp(amber_serv_t *server, amber_world_t *world, char **cmd);

/**
 * @brief Structure representing an Amber command server.
 *
 * This structure holds information about a command that
 * can be executed by the server.
 * It consists of a command string and a function pointer to
 * the corresponding command handler.
 */
typedef struct amber_command_server_s {
    char *command; /**< The command string. */
    void (*func)(amber_serv_t *, amber_world_t *, char **);
} amber_command_server_t;

/**
 * @brief Array of amber_command_server_t objects.
 *
 * This variable represents an array of `amber_command_server_t` objects.
 * It is declared as `extern` to indicate that its definition is provided
 * in another file.
 * The array contains the command servers used in the application.
 */
extern const amber_command_server_t command_serv[];

#endif /* !AMBER_COMMAND_SERVER_H_ */
