/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_command_graphical
*/

#ifndef AMBER_COMMAND_GRAPHICAL_H_
    #define AMBER_COMMAND_GRAPHICAL_H_

    #include "amber_init.h"
    #include "amber_manage_client.h"

    #define CONTANT_MAP "bct %d %d %d %d %d %d %d %d %d\n"

/**
 * @brief Struct representing a graphical command.
 *
 * This struct holds information about a graphical command, including
 * the command string
 * and a function pointer to the corresponding function that handles
 * the command.
 */
typedef struct graphical_command_s {
    char *_command;
    void (*_func)(amber_client_t *client, char **arg);
    void (*_execute)(command_t *cmd, amber_client_t *client,
        amber_world_t *world, list_t *clients);
    type_command_t _id;
} graphical_command_t;

/**
 * @brief Manages the graphical command for the Amber server.
 *
 * This function is responsible for handling the graphical
 * command received from a client.
 *
 * @param client The client sending the command.
 * @param arg The arguments passed with the command.
 */

void amber_manage_command_grahical(amber_client_t *client, char **arg);

/**
 * Executes the 'msz' command for the graphical client.
 *
 * This function is responsible for executing the 'msz' command received from
 * the graphical client. It takes the command object, the client object, the
 * world object, and the list of clients as parameters.
 *
 * @param cmd The command object representing the 'msz' command.
 * @param client The graphical client object.
 * @param world The world object representing the game world.
 * @param clients The list of all connected clients.
 */
void amber_graphic_execute_msz(command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Executes the "msz" command for the graphical client.
 *
 * This function is responsible for handling the "msz" command received
 * from the graphical client.
 * It takes a pointer to the amber_client_t structure and a pointer to
 * the argument array as parameters.
 *
 * @param client A pointer to the amber_client_t structure representing
 * the graphical client.
 * @param arg    A pointer to the argument array containing the command
 * arguments.
 */
void amber_graphic_msz(amber_client_t *client, char **arg);

/**
 * Executes the BCT command for the graphical client.
 *
 * This function is responsible for executing the BCT command
 * for the graphical client.
 * It takes in the command structure, the client structure,
 * the world structure, and the list of clients.
 *
 * @param cmd The command structure containing the BCT command.
 * @param client The graphical client structure.
 * @param world The world structure.
 * @param clients The list of clients.
 */
void amber_graphic_execute_bct(command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Executes the "bct" command for the graphical client.
 *
 * This function is responsible for executing the "bct" command
 * for the graphical client.
 * It takes a pointer to the amber_client_t structure and an array
 * of strings as arguments.
 * The array of strings is not used in this function and is marked as UNUSED.
 *
 * @param client A pointer to the amber_client_t structure representing
 * the graphical client.
 * @param arg An array of strings representing the command arguments (UNUSED).
 */
void amber_graphic_bct(amber_client_t *client, UNUSED char **arg);

/**
 * Executes the MCT command for the graphical client.
 *
 * This function is responsible for executing the MCT command for
 * the graphical client.
 * It takes a command object, a client object, a world object, and a
 * list of clients as parameters.
 *
 * @param cmd The command object (unused).
 * @param client The graphical client object.
 * @param world The world object.
 * @param clients The list of clients.
 */
void amber_graphic_execute_mct(UNUSED command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Sends the MCT command to the graphical client.
 *
 * This function is responsible for sending the MCT (Map Content)
 * command to the graphical client.
 * The MCT command requests the graphical client to retrieve and display
 * the current state of the game map.
 *
 * @param client The graphical client to send the command to.
 * @param arg Unused argument.
 */
void amber_graphic_mct(amber_client_t *client, UNUSED char **arg);

/**
 * Executes the "sgt" command for the graphical client.
 *
 * This function is responsible for executing the "sgt" command for
 * the graphical client.
 * It takes a command object, a client object, a world object, and a
 * list of clients as parameters.
 *
 * @param cmd The command object (unused).
 * @param client The graphical client object.
 * @param world The world object.
 * @param clients The list of clients.
 */
void amber_graphic_execute_sgt(UNUSED command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Sends the "sgt" command to the graphical client.
 *
 * This function is responsible for sending the "sgt"
 * command to the graphical client.
 * The "sgt" command is used to retrieve the current
 * time unit value from the server.
 *
 * @param client The graphical client to send the command to.
 * @param arg Unused argument.
 */
void amber_graphic_sgt(amber_client_t *client, UNUSED char **arg);

/**
 * Executes the "sst" command for the graphical client.
 *
 * This function is responsible for executing the "sst" command for
 * the graphical client.
 * It takes in the command structure, the client structure, the world
 * structure, and the list of clients.
 *
 * @param cmd The command structure containing the command information.
 * @param client The graphical client structure.
 * @param world The world structure containing the game state.
 * @param clients The list of clients connected to the server.
 */
void amber_graphic_execute_sst(command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Sets the state of the graphical client.
 *
 * This function is used to set the state of the graphical client.
 *
 * @param client The graphical client.
 * @param arg The arguments passed to the function.
 */
void amber_graphic_sst(amber_client_t *client, char **arg);

/**
 * Executes the TNA command for the graphical client.
 *
 * This function is responsible for executing the TNA command, which sends the
 * names of all the teams in the game to the graphical client. It takes in the
 * command, the client, the world, and the list of clients as parameters.
 *
 * @param cmd The command to be executed (unused).
 * @param client The graphical client.
 * @param world The game world.
 * @param clients The list of all clients.
 */
void amber_graphic_execute_tna(UNUSED command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Sends the TNA command to the graphical client.
 *
 * This function is responsible for sending the TNA command to
 * the graphical client.
 * The TNA command is used to request the names of all the teams in the game.
 *
 * @param client The graphical client to send the command to.
 * @param arg Unused argument.
 */
void amber_graphic_tna(amber_client_t *client, UNUSED char **arg);

/**
 * Executes the PPO command for a graphical client.
 *
 * This function is responsible for executing the PPO command, which is used
 * to retrieve the position and orientation of a player. It takes as input
 * the command structure, the graphical client, the world state, and the list
 * of connected clients.
 *
 * @param cmd The command structure containing the PPO command.
 * @param client The graphical client that sent the command.
 * @param world The current state of the game world.
 * @param clients The list of connected clients.
 */
void amber_graphic_execute_ppo(command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Updates the position and orientation of a graphical client.
 *
 * This function is responsible for updating the position and orientation of
 * a graphical client.
 *
 * @param client The graphical client to update.
 * @param arg The arguments for the update.
 */
void amber_graphic_ppo(amber_client_t *client, char **arg);

/**
 * Executes the "plv" command for the graphical client.
 *
 * This function is responsible for executing the "plv" command,
 * which is used to
 * retrieve the player's level information for the graphical client.
 * It takes in
 * the command structure, the client structure, the world structure,
 * and the list
 * of clients as parameters.
 *
 * @param cmd The command structure containing the parsed command information.
 * @param client The graphical client structure.
 * @param world The world structure containing the game state.
 * @param clients The list of all connected clients.
 */
void amber_graphic_execute_plv(command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Sends the player level (plv) command to the graphical client.
 *
 * This function is responsible for sending the player level (plv) command to
 * the graphical client.
 * It takes a pointer to the `amber_client_t` structure representing
 * the graphical client and a double pointer to the argument array.
 *
 * @param client A pointer to the `amber_client_t` structure representing
 * the graphical client.
 * @param arg A double pointer to the argument array.
 */
void amber_graphic_plv(amber_client_t *client, char **arg);

/**
 * Executes the "pin" command for graphical clients.
 *
 * This function is responsible for executing the "pin" command for
 * graphical clients.
 * It takes a pointer to the command structure, a pointer to the
 * client structure,
 * a pointer to the world structure, and a pointer to the list of
 * clients as parameters.
 *
 * @param cmd     Pointer to the command structure.
 * @param client  Pointer to the client structure.
 * @param world   Pointer to the world structure.
 * @param clients Pointer to the list of clients.
 */
void amber_graphic_execute_pin(command_t *cmd, amber_client_t *client,
    amber_world_t *world, list_t *clients);

/**
 * @brief Handles the 'graphic_pin' command for the Amber server.
 *
 * This function is responsible for processing the 'graphic_pin' command
 * received from a graphical client.
 * It takes a pointer to the client structure and a pointer to an array of
 * arguments as parameters.
 *
 * @param client A pointer to the amber_client_t structure representing
 * the graphical client.
 * @param arg An array of strings containing the command arguments.
 */
void amber_graphic_pin(amber_client_t *client, char **arg);

/**
 * @brief Executes the graphical loop for the Amber server.
 *
 * This function is responsible for running the graphical loop of
 * the Amber server.
 * It takes a pointer to the server structure and a pointer to
 * the world structure as parameters.
 *
 * @param server A pointer to the Amber server structure.
 * @param world A pointer to the Amber world structure.
 */
void amber_graphic_loop(amber_serv_t *server, amber_world_t *world);

/**
 * @file amber_command_graphical.h
 * @brief Header file containing the declaration of the
 * graphical_commands array.
 *
 * This file declares the external array graphical_commands[], which contains
 * the graphical commands.
 * The graphical_commands array is used for storing and accessing the graphical
 * commands in the server.
 */
extern const graphical_command_t graphical_commands[];

#endif /* !AMBER_COMMAND_GRAPHICAL_H_ */