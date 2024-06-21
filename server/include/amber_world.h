/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_world
*/

#pragma once
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include "common_defines.h"
    #include "list.h"
    #include "string_array.h"
    #include "amber_check_arg.h"
    #include "amber_clock.h"
    #include "map.h"
    #include "amber_queue_command.h"

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    #define RAND(x) (rand() % x)

    #define INV_TMP "mendiane %d, phiras %d, thystame %d]\n"
    #define INVENTORY "[food %d, linemate %d, deraumere %d, sibur %d, " INV_TMP

/**
 * @brief Structure representing an egg in the game world.
 */
typedef struct egg_s {
    int _x; /**< The x-coordinate of the egg. */
    int _y; /**< The y-coordinate of the egg. */
    char *_team; /**< The team that the egg belongs to. */
    int _hatching_time; /**< The remaining time until the egg hatches. */
    direction_t _direction; /**< The direction the egg is facing. */
    int _id; /**< The unique identifier of the egg. */
} egg_t;

/**
 * @brief Represents a box in the game world.
 *
 * This struct contains the quantities of different resources present in a box.
 * The resources include food, linemate, deraumere, sibur, mendiane, phiras,
 * and thystame.
 */
typedef struct box_s {
    int _food;
    int _linemate;
    int _deraumere;
    int _sibur;
    int _mendiane;
    int _phiras;
    int _thystame;
    int _players;
    int _eggs;
} box_t;

/**
 * @brief Structure representing a pair of values.
 */
typedef struct pair_s {
    int _c_value; /**< The current value. */
    int _m_value; /**< The maximum value. */
} pair_int_t;

typedef struct amber_trantor_s {
    int _x;
    int _y;
    int _level;
    int _id;
    direction_t _direction;
    char *_team_name;
    box_t *_inventory;
    bool _is_graphical;
    bool _is_incantating;
    unsigned long _ellapsed_time;
    unsigned long _clock_food;
    queue_command_t *_queue_command;
} amber_trantor_t;

/**
 * @brief Structure representing the Amber World.
 *
 * This structure holds information about the Amber World, including its width,
 * height, and the cases it contains.
 *
 * @param _width The width of the Amber World.
 * @param _height The height of the Amber World.
 * @param _clientsNb The number of clients in the Amber World.
 * @param _teams_name The names of the teams in the Amber World.
 * @param _case The cases in the Amber World.
 * @param _food_info The information about the food in the Amber World.
 * @param _linemate_info The information about the linemate in the Amber World.
 * @param _deraumere_info The information about the deraumere in
 * the Amber World.
 * @param _sibur_info The information about the sibur in the Amber World.
 * @param _mendiane_info The information about the mendiane in the Amber World.
 * @param _phiras_info The information about the phiras in the Amber World.
 * @param _thystame_info The information about the thystame in the Amber World.
 * @param _eggs The eggs in the Amber World.
 * @param _freq The frequency of the resources in the Amber World.
 * @param _clock The clock of the Amber World.
 * @param _last_egg_id The last egg ID in the Amber World.
 */
typedef struct amber_world_s {
    int _width;
    int _height;
    int _clientsNb;
    char **_teams_name;
    box_t **_case;
    pair_int_t _food_info;
    pair_int_t _linemate_info;
    pair_int_t _deraumere_info;
    pair_int_t _sibur_info;
    pair_int_t _mendiane_info;
    pair_int_t _phiras_info;
    pair_int_t _thystame_info;
    list_t *_eggs;
    double _freq;
    unsigned long _clock;
    int _last_egg_id;
    list_t *_incantation_grp;
    map_t *_playersMap;
} amber_world_t;

/**
 * Creates a new instance of the amber_world_t struct and initializes
 * its properties.
 *
 * @param arg The arguments for creating the world.
 * @return A pointer to the newly created amber_world_t struct,
 * or NULL if memory allocation fails.
 */
amber_world_t *amber_create_world(args_t *args);

/**
 * @brief Destroys an amber_world_t object.
 *
 * This function is responsible for deallocating the memory
 * used by an amber_world_t object.
 *
 * @param world The amber_world_t object to be destroyed.
 */
void destroy_amber_world(amber_world_t *world);

/**
 * @brief Refills the given amber world.
 *
 * This function refills the specified amber world with resources.
 *
 * @param world The amber world to be refilled.
 */
void amber_refill_world(amber_world_t *world);

/**
 * Displays the amber world.
 *
 * This function displays the given amber world.
 * It can optionally display the world
 * inside a box.
 *
 * @param fd    The file descriptor to write the output to.
 * @param world The amber world to be displayed.
 * @param box   A boolean value indicating whether
 * to display the world inside a box.
 */
void amber_display_world(int fd, amber_world_t *world, bool box);

/**
 * @brief Creates a new egg in the Amber World.
 *
 * This function creates a new egg in the Amber World based
 * on the provided arguments.
 *
 * @param ap A pointer to the variable argument list.
 * @return A pointer to the newly created egg.
 */
void *amber_create_egg(va_list *ap);

/**
 * @brief Destroys an egg object.
 *
 * This function frees the memory allocated for an
 * egg object and its associated teams.
 *
 * @param gree A pointer to the egg object to be destroyed.
 */
void amber_destroy_egg(void *gree);

/**
 * Retrieves an egg from the given world that belongs to the specified team.
 *
 * @param world The amber_world_t structure representing the game world.
 * @param team The name of the team to which the egg belongs.
 * @return A pointer to the egg if found, or NULL if no matching egg is found.
 */
egg_t *amber_get_egg_by_team(amber_world_t *world, char *team);

/**
 * @brief Converts a box_t structure into a string representation.
 *
 * This function takes a pointer to a box_t structure and converts it
 * into a string representation.
 * The resulting string contains information about the box, such as its
 * coordinates and contents.
 *
 * @param box A pointer to the box_t structure to be converted.
 * @return A dynamically allocated string representing the box.
 */
char *amber_world_case_stringify(box_t *box);

/**
 * Retrieves the number of eggs belonging to a specific team in
 * the given world.
 *
 * @param world The pointer to the amber_world_t structure representing
 * the game world.
 * @param team The name of the team for which to retrieve the number of eggs.
 * @return The number of eggs belonging to the specified team.
 */
int amber_get_nbr_eggs_by_team(amber_world_t *world, char *team);

/**
 * @brief Initializes a new box in the Amber World.
 *
 * This function creates and initializes a new box in the Amber World.
 * The box is represented by the `box_t` data structure.
 *
 * @return A pointer to the newly created box.
 */
box_t *amber_world_case_init(void);

/**
 * Initializes an egg in the Amber world.
 *
 * @param world The Amber world to initialize the egg in.
 */
void amber_init_egg(amber_world_t *world);

/**
 * @brief Checks if there is a winner in the Amber World game.
 *
 * This function checks if there is a winner in the Amber World game
 * by analyzing the state of the clients and the Trantor world.
 *
 * @param clients A pointer to the list of clients in the game.
 * @param trantor A pointer to the Trantor world structure.
 * @return Returns true if there is a winner, false otherwise.
 */
bool amber_check_winner(list_t *clients, amber_trantor_t *trantor);
