/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_logic
*/

#ifndef AMBER_LOGIC_H_
    #define AMBER_LOGIC_H_

    #include "amber_queue_command.h"
    #include "amber_init.h"
    #include "amber_clock.h"

    #define ABS(n) (n < 0) ? -n : n

/**
 * @brief Structure representing a logic command.
 *
 * This structure holds information about a logic command,
 * including the command type
 * and a function pointer to the corresponding logic function.
 */
typedef struct logic_command_s {
    type_command_t _command; /**< The command type. */
    void (*_func)
        (amber_client_t *cli, amber_world_t *wrld,
        amber_serv_t *srv); /**< Function pointer to the logic function. */
} logic_command_t;

/**
 * @brief Array of logic commands.
 *
 * This array contains all the logic commands available in the system.
 * Each logic command is represented by a logic_command_t structure.
 */
extern const logic_command_t logic_commands[];

/**
 * @brief Clamps a value between a minimum and maximum range.
 *
 * @param min The minimum value of the range.
 * @param current The value to clamp.
 * @param max The maximum value of the range.
 * @return The clamped value.
 */
int clamp(int min, int current, int max);

/**
 * @brief Clamps a value between a minimum and maximum range.
 * This function is similar to `clamp`, but it is used for
 * floating-point values.
 *
 * @param min The minimum value of the range.
 * @param current The value to clamp.
 * @param max The maximum value of the range.
 * @return The clamped value.
 */
int real_clamp(int min, int current, int max);

/**
 * @brief Checks if a client is still alive and disconnects it if not.
 *
 * @param server The server instance.
 */
void amber_check_client_alive(amber_serv_t *server);

/**
 * @brief Sends a message to a client.
 *
 * @param client The client to send the message to.
 * @param message The message to send.
 */
void send_client_message(amber_client_t *client, const char *message);

/**
 * @brief Turns the client to the left in the world.
 *
 * @param client The client to turn.
 * @param world The world instance.
 * @param serv The server instance.
 */
void amber_logic_forward(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv);

/**
 * @brief Turns the client to the right in the world.
 *
 * @param client The client to turn.
 * @param world The world instance.
 * @param serv The server instance.
 */
void amber_logic_right(amber_client_t *client, UNUSED amber_world_t *world,
    UNUSED amber_serv_t *serv);

/**
 * @brief Turns the client to the left in the world.
 *
 * @param client The client to turn.
 * @param world The world instance.
 * @param serv The server instance.
 */
void amber_logic_left(amber_client_t *client, UNUSED amber_world_t *world,
    UNUSED amber_serv_t *serv);

/**
 * @brief Performs a look action for the client in the world.
 *
 * @param client The client to perform the look action for.
 * @param world The world instance.
 * @param serv The server instance.
 */
void amber_logic_look(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv);

/**
 * @brief Retrieves the inventory of the client.
 *
 * @param client The client to retrieve the inventory for.
 * @param world The world instance.
 * @param serv The server instance.
 */
void amber_logic_inventory(amber_client_t *client,
    UNUSED amber_world_t *world, UNUSED amber_serv_t *serv);

/**
 * @brief Performs a broadcast action for the client in the world.
 *
 * @param client The client to perform the broadcast action for.
 * @param world The world instance.
 * @param serv The server instance.
 */
void amber_logic_broadcast(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);

void amber_logic_eject(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);

/**
 * @brief The main logic loop for the server.
 *
 * @param serv The server instance.
 * @param world The world instance.
 */
void amber_logic_loop(amber_serv_t *serv, amber_world_t *world);

#endif /* !AMBER_LOGIC_H_ */
