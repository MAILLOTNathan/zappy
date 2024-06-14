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
    #include <math.h>

    #define ABS(n) (n < 0) ? -n : n


typedef struct pos_s {
    int x;
    int y;
} pos_t;

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
 * @param world The world instance.
 */
void amber_check_client_alive(amber_serv_t *server, amber_world_t *world);

/**
 * @brief Sends a message to a client.
 *
 * @param client The client to send the message to.
 * @param message The message to send.
 */
void send_cli_msg(amber_client_t *client, const char *message);

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

/**
 * Ejects the client from the world in the Zappy server.
 *
 * @param client The client to eject.
 * @param world The world in which the client is located.
 * @param serv The server instance.
 */
void amber_logic_eject(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);

/**
 * Forks the logic for the given client in the world.
 *
 * @param client The client to fork the logic for.
 * @param world The world in which the client exists.
 * @param serv The server instance.
 */
void amber_logic_fork(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv);

/**
 * Connects the given client to the world.
 *
 * This function is responsible for establishing a connection between
 * the client and the world.
 * It takes a pointer to the `amber_client_t` structure representing the
 * client and a pointer to
 * the `amber_world_t` structure representing the world. The `amber_serv_t`
 * structure is not used
 * in this function and is marked as `UNUSED`.
 *
 * @param client A pointer to the `amber_client_t` structure representing
 * the client.
 * @param world A pointer to the `amber_world_t` structure representing
 * the world.
 * @param serv A pointer to the `amber_serv_t` structure representing
 * the server (UNUSED).
 */
void amber_logic_connect_nbr(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv);

/**
 * @brief The main logic loop for the server.
 *
 * @param serv The server instance.
 * @param world The world instance.
 */
void amber_logic_loop(amber_serv_t *serv, amber_world_t *world);

/**
 * Calculates the distance between two points on a grid.
 *
 * @param src The source point.
 * @param dest The destination point.
 * @param max The maximum value of the grid.
 * @return The distance between the source and destination points.
 */
int get_distance(int src, int dest, int max);

/**
 * Calculates the direction from the source point to the destination point
 * on a grid.
 *
 * @param src The source point.
 * @param dest The destination point.
 * @param max The maximum value of the grid.
 * @return The direction from the source to the destination point.
 */
// int get_direction_action(int src, int dest, int max);

/**
 * Initializes a boolean array representing the perimeter of a grid.
 *
 * @param directions An array of directions.
 * @return A boolean array representing the perimeter of the grid.
 */
bool *initialize_perimeter(int *directions);

/**
 * @brief Retrieves the direction based on the given perimeter and client.
 *
 * This function takes a boolean array representing the perimeter and a
 * pointer to an amber_client_t structure.
 * It calculates and returns the direction based on the given perimeter
 * and client.
 *
 * @param perimeter A boolean array representing the perimeter.
 * @param client A pointer to an amber_client_t structure.
 * @return The direction calculated based on the perimeter and client.
 */
int get_direction_by_perimeter(bool *perimeter, amber_client_t *client);

pos_t plotline(pos_t *m, pos_t *m2);

/**
 * @brief Calculates the precise perimeter based on the given perimeter
 * and distances.
 *
 * This function takes in a boolean array representing the perimeter and
 * an integer array
 * representing the distances. It calculates the precise perimeter based
 * on these inputs.
 *
 * @param perim The boolean array representing the perimeter.
 * @param distances The integer array representing the distances.
 * @return A boolean array representing the precise perimeter.
 */
bool *precise_perimeter(bool *perim, int *distances);

/**
 * Takes an object from the Amber world to the client.
 *
 *
 * @param client The client performing the action.
 * @param world The world in which the action is being performed.
 * @param serv The server on which the action is being performed.
 */
void amber_logic_take(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv);

/**
 * Set an object from the inventory to the world.
 *
 *
 * @param client The Amber client to set the object.
 * @param world The Amber world information.
 * @param serv The Amber server information (unused).
 */
void amber_logic_set(amber_client_t *client, amber_world_t *world,
    UNUSED amber_serv_t *serv);

/**
 * @brief Executes the incantation logic for a client in the Zappy server.
 *
 * This function is responsible for handling the incantation logic for a
 * specific client
 * in the Zappy server. It takes a pointer to the client structure, a pointer
 * to the world
 * structure, and a pointer to the server structure as arguments.
 *
 * @param client A pointer to the client structure.
 * @param world A pointer to the world structure.
 * @param serv A pointer to the server structure (UNUSED).
 */
void amber_logic_incantation(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);

#endif /* !AMBER_LOGIC_H_ */
