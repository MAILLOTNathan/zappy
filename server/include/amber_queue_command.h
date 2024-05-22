/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_queue_command
*/

#ifndef AMBER_QUEUE_COMMAND_H_
    #define AMBER_QUEUE_COMMAND_H_

    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>

/**
 * @brief Enumeration of command types.
 *
 * This enumeration represents the different types of commands that can be
 * executed in the program. Each command type corresponds to a specific action
 * that can be performed by the program.
 */
typedef enum type_command_s {
    T_FORWARD,          /**< Move the player forward */
    T_RIGHT,            /**< Turn the player to the right */
    T_LEFT,             /**< Turn the player to the left */
    T_LOOK,             /**< Look for resources around the player */
    T_INVENTORY,        /**< Get the player's inventory */
    T_BROADCAST,        /**< Broadcast a message to other players */
    T_CONNECT_NBR,      /**< Connect to a specific number of players */
    T_FORK,             /**< Fork a new player */
    T_EJECT,            /**< Eject a player from the current tile */
    T_TAKE,             /**< Take a resource from the current tile */
    T_SET,              /**< Set a resource on the current tile */
    T_INCANTATION       /**< Perform an incantation */
} type_command_t;

/**
 * @brief Structure representing a command.
 *
 * This structure holds information about a command, including its argument,
 * ID, and time.
 * @param _arg The argument of the command.
 * @param _id The ID of the command.
 * @param _time The time of the command.
 */
typedef struct command_s {
    char *_arg; /**< The argument of the command. */
    int _id;    /**< The ID of the command. */
    int _time;  /**< The time of the command. */
} command_t;

/**
 * @struct queue_command_t
 * @brief Represents a node in a queue of commands.
 *
 * This structure is used to store a command and a reference
 * to the next node in the queue.
 * @param _command The command stored in the node.
 * @param _next A pointer to the next node in the queue.
 */
typedef struct queue_command_s {
    command_t *_command;
    struct queue_command_s *_next;
} queue_command_t;

/**
 * Adds a command to the back of the queue.
 *
 * @param q The pointer to the queue.
 * @param command The command to be added to the queue.
 * @return `true` if the command was successfully added, `false` otherwise.
 */
bool queue_push_back(queue_command_t **q, command_t *command);

/**
 * Adds a new command to the end of the queue.
 *
 * @param q The pointer to the queue.
 * @param arg The command argument.
 * @param time The command execution time.
 * @param id The command ID.
 * @return `true` if the command was successfully added, `false` otherwise.
 */
bool queue_push_back_d(queue_command_t **q, char *arg, int time, int id);

/**
 * @brief Removes and returns the front element from the queue.
 *
 * This function removes and returns the front element
 * from the specified queue.
 *
 * @param q A pointer to the queue from which to remove the front element.
 * @return A pointer to the removed front element,
 * or NULL if the queue is empty.
 */
command_t *queue_pop_front(queue_command_t **q);

/**
 * Displays the contents of the queue_command_t structure.
 *
 * @param q The queue_command_t structure to be displayed.
 */
void queue_display(queue_command_t *q);

/**
 * @brief Destroys a queue of commands.
 *
 * This function frees the memory allocated for the queue and all its elements.
 *
 * @param q A pointer to a pointer to the queue to be destroyed.
 */
void queue_destroy(queue_command_t **q);

/**
 * Calculates the size of the queue_command.
 *
 * @param queue A pointer to the queue_command.
 * @return The size of the queue_command.
 */
int queue_command_size(queue_command_t *queue);

#endif /* !AMBER_QUEUE_COMMAND_H_ */
