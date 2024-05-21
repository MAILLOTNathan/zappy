/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_process
*/

#ifndef AMBER_PROCESS_H_
    #define AMBER_PROCESS_H_

    #include "amber_init.h"
    #include "string_array.h"
    #include "amber_world.h"

/**
 * Accepts a new client connection and adds it to the server's client list.
 *
 * @param server The Amber server instance.
 */
void amber_accept_client(amber_serv_t *server, amber_world_t *world);

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
 * @param world The Amber world instance.
 */
void amber_listening(amber_serv_t *server, amber_world_t *world);

#endif /* !AMBER_PROCESS_H_ */
