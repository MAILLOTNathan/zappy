/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_command_ai
*/

#ifndef AMBER_MANAGE_COMMAND_AI_H_
    #define AMBER_MANAGE_COMMAND_AI_H_

    #include "amber_init.h"
    #include "amber_queue_command.h"
    #include "string_array.h"
    #include "amber_logic.h"

typedef struct ai_command_s {
    char *_command;
    type_command_t _type;
    void (*_func)(amber_client_t *client, char **arg);
} ai_command_t;

/**
 * @brief Moves the AI client forward in the game.
 *
 * This function is responsible for moving the AI client forward in the game.
 * It takes a pointer to the `amber_client_t` structure representing the client
 * and a pointer to the buffer containing the command.
 *
 * @param client A pointer to the `amber_client_t` structure representing
 * the client.
 * @param arg A pointer to the buffer containing the command.
 */
void amber_ai_forward(amber_client_t *client, char **arg);

/**
 * @brief Manages the command received from an AI client.
 *
 * This function is responsible for processing the command received
 * from an AI client and performing the necessary actions based on the command.
 *
 * @param client A pointer to the `amber_client_t` structure representing
 * the AI client.
 * @param arg A pointer to the buffer containing the command.
 */
void amber_manage_command_ai(amber_client_t *client, char **arg);

/**
 * Moves the AI player to the right.
 *
 * @param client The client representing the AI player.
 * @param arg Unused argument.
 */
void amber_ai_right(amber_client_t *client, UNUSED char **arg);

/**
 * @brief Moves the AI client to the left.
 *
 * This function is responsible for moving the AI client to the left.
 *
 * @param client The AI client to move.
 * @param arg Unused argument.
 */
void amber_ai_left(amber_client_t *client, UNUSED char **arg);

/**
 * @brief Executes the "look" command for the AI client.
 *
 * This function is responsible for executing the "look" command
 * for the AI client.
 * It takes a pointer to the `amber_client_t` structure and an
 * unused argument array.
 *
 * @param client A pointer to the `amber_client_t`
 * structure representing the AI client.
 * @param arg An unused argument array.
 */
void amber_ai_look(amber_client_t *client, UNUSED char **arg);

/**
 * @brief Handles the inventory command for the Amber AI.
 *
 * This function is responsible for handling
 * the inventory command for the Amber AI.
 * It takes a pointer to the `amber_client_t`
 * structure and an unused array of strings as arguments.
 *
 * @param client A pointer to the `amber_client_t`
 * structure representing the client.
 * @param arg An unused array of strings.
 */
void amber_ai_inventory(amber_client_t *client, char **arg);

/**
 * Sends a broadcast message from the AI client to the server.
 *
 * @param client The AI client sending the broadcast.
 * @param arg The arguments for the broadcast command.
 */
void amber_ai_broadcast(amber_client_t *client, char **arg);

/**
 * @brief Connects the AI client to the nearest available server slot.
 *
 * This function is responsible for connecting the AI client
 * to the nearest available server slot.
 * It takes a pointer to the `amber_client_t` structure representing
 * the AI client and an unused
 * array of strings as arguments.
 *
 * @param client A pointer to the `amber_client_t` structure representing
 * the AI client.
 * @param arg An unused array of strings.
 */
void amber_ai_connect_nbr(amber_client_t *client, UNUSED char **arg);

extern const ai_command_t ai_commands[];

#endif /* !AMBER_MANAGE_COMMAND_AI_H_ */
