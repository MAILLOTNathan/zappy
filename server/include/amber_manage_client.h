/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_manage_client
*/

#ifndef AMBER_MANAGE_CLIENT_H_
    #define AMBER_MANAGE_CLIENT_H_

    #include "common_defines.h"
    #include "amber_init.h"
    #include "amber_world.h"

/**
 * Creates a new Amber client.
 *
 * This function allocates memory for a new `amber_client_t
 * structure and initializes its fields.
 * The file descriptor for the TCP connection is obtained from
 * the variable argument list `ap`.
 *
 * @param ap A pointer to the variable argument list containing
 * the file descriptor for the TCP connection.
 * @return A pointer to the newly created `amber_client_t`
 * structure, or `NULL` if memory allocation fails.
 */
void *amber_create_client(va_list *ap);

/**
 * @brief Destroys an Amber client.
 *
 * This function closes the TCP socket associated with the client
 * and frees the memory allocated for the client structure.
 *
 * @param client A pointer to the Amber client structure to be destroyed.
 */
void amber_destroy_client(void *client);

/**
 * @brief Reads data from a client socket and handles it.
 *
 * This function is responsible for reading data from a client
 * socket and handling it appropriately.
 * It takes a pointer to the server structure and a pointer
 * to the client structure as parameters.
 *
 * @param server A pointer to the server structure.
 * @param client A pointer to the client structure.
 * @param clients A pointer to the list of clients.
 */
void amber_manage_client_read(amber_world_t *world, amber_serv_t *server,
    amber_client_t *client, list_t *clients);

/**
 * @brief Retrieves the number of clients belonging to a specific team
 * in the Amber server.
 *
 * This function returns the number of clients that are currently connected
 * to the Amber server
 * and belong to the specified team.
 *
 * @param server A pointer to the Amber server structure.
 * @param team The name of the team.
 * @return The number of clients belonging to the specified team.
 */
int amber_get_nbr_clients_by_team(amber_serv_t *server, char *team);

/**
 * @brief Retrieves a client from the server by its ID.
 *
 * This function searches for a client in the server's client list
 * based on its ID.
 *
 * @param clients A pointer to the list of clients.
 * @param id The ID of the client to retrieve.
 * @return A pointer to the client if found, or NULL if not found.
 */
amber_client_t *amber_get_client_by_id(list_t *clients, int id);

/**
 * Initializes an Amber client.
 *
 * This function initializes an Amber client by setting up the necessary
 * connections and resources. It takes a pointer to an `amber_client_t`
 * structure, a pointer to an `amber_serv_t` structure, a pointer to an
 * `amber_world_t` structure, and a double pointer to a character array.
 *
 * @param client A pointer to the `amber_client_t` structure to be initialized.
 * @param serv A pointer to the `amber_serv_t` structure representing
 * the server.
 * @param world A pointer to the `amber_world_t` structure representing
 * the world.
 * @param arg A double pointer to a character array representing the arguments.
 * @return `true` if the client is successfully initialized, `false` otherwise.
 */
bool amber_init_client(amber_client_t *client, amber_serv_t *serv,
    amber_world_t *world, char **arg);

/**
 * @brief Formats a string and sends it to the specified client.
 *
 * This function takes a variable number of arguments and formats them
 * according to the specified format string.
 * The resulting formatted string is then sent to the specified client.
 *
 * @param client A pointer to the `amber_client_t` structure representing the
 * client.
 * @param format The format string specifying how the arguments should be
 * formatted.
 * @param ... Additional arguments to be formatted according to the format
 * string.
 */
void snprintfizer(amber_client_t *client, char *format, ...);

#endif /* !AMBER_MANAGE_CLIENT_H_ */
