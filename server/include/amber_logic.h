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

typedef struct logic_command_s {
    type_command_t _command;
    void (*_func)(amber_client_t *cli, amber_world_t *world,
        amber_serv_t *serv);
} logic_command_t;

extern const logic_command_t logic_commands[];

int clamp(int min, int current, int max);
int real_clamp(int min, int current, int max);

void amber_check_client_alive(amber_serv_t *server);
void send_client_message(amber_client_t *client, const char *message);

void amber_logic_forward(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);
void amber_logic_left(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);
void amber_logic_right(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);
void amber_logic_look(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);
void amber_logic_inventory(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);

void amber_logic_broadcast(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);

void amber_logic_eject(amber_client_t *client, amber_world_t *world,
    amber_serv_t *serv);

void amber_logic_loop(amber_serv_t *serv, amber_world_t *world);

#endif /* !AMBER_LOGIC_H_ */
