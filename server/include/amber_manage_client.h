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
 */
void amber_manage_client_read(amber_serv_t *server, amber_client_t *client);

#endif /* !AMBER_MANAGE_CLIENT_H_ */
