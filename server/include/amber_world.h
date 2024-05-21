/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_world
*/

#ifndef AMBER_WORLD_H_
    #define AMBER_WORLD_H_

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include "common_defines.h"
    #include "list.h"

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    #define RAND(x) (rand() % x)

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
} box_t;

/**
 * @brief Structure representing a pair of values.
 */
typedef struct pair_s {
    int _c_value; /**< The current value. */
    int _m_value; /**< The maximum value. */
} pair_t;

/**
 * @brief Structure representing the Amber World.
 *
 * This structure holds information about the Amber World, including its width,
 * height, and the cases it contains.
 *
 * @param _width The width of the Amber World.
 * @param _height The height of the Amber World.
 * @param _case The cases in the Amber World.
 * @param _food_info The information about the food in the Amber World.
 * @param _linemate_info The information about the linemate in the Amber World.
 * @param _deraumere_info The information about the deraumere in
 * the Amber World.
 * @param _sibur_info The information about the sibur in the Amber World.
 * @param _mendiane_info The information about the mendiane in the Amber World.
 * @param _phiras_info The information about the phiras in the Amber World.
 * @param _thystame_info The information about the thystame in the Amber World.
 */
typedef struct amber_world_s {
    int _width;
    int _height;
    box_t **_case;
    pair_t _food_info;
    pair_t _linemate_info;
    pair_t _deraumere_info;
    pair_t _sibur_info;
    pair_t _mendiane_info;
    pair_t _phiras_info;
    pair_t _thystame_info;
    list_t *_eggs;
} amber_world_t;

/**
 * @brief Creates a new instance of an Amber World.
 *
 * This function creates a new instance of an Amber World with the
 * specified width and height.
 *
 * @param width The width of the Amber World.
 * @param height The height of the Amber World.
 * @return A pointer to the created Amber World instance.
 */
amber_world_t *amber_create_world(int width, int height, char **teams);

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
 * @param world The amber world to be displayed.
 * @param box   A boolean value indicating whether
 * to display the world inside a box.
 */
void amber_display_world(amber_world_t *world, bool box);

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

#endif /* !AMBER_WORLD_H_ */
