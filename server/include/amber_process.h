/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_process
*/

#ifndef AMBER_PROCESS_H_
    #define AMBER_PROCESS_H_

    #include "amber_init.h"

/**
 * Accepts a new client connection and adds it to the server's client list.
 *
 * @param server The Amber server instance.
 */
void amber_accept_client(amber_serv_t *server);

/**
 * Manages the clients connected to the Amber server.
 *
 * @param server The Amber server instance.
 */
void amber_manage_client(amber_serv_t *server);

/**
 * @brief Function to handle the main listening loop of the Amber server.
 *
 * This function continuously listens for incoming connections and
 * manages client requests.
 *
 * @param server The Amber server instance.
 */
void amber_listening(amber_serv_t *server);

#endif /* !AMBER_PROCESS_H_ */
