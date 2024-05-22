/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** amber_wolrd
*/

#include "amber_world.h"

static void init_pair(pair_t *pair, int width, int height, double density)
{
    pair->_c_value = 0;
    pair->_m_value = width * height * density;
}

static void init_info_world(amber_world_t *world)
{
    init_pair(&world->_food_info, world->_width, world->_height,
    FOOD_DENSITY);
    init_pair(&world->_linemate_info, world->_width, world->_height,
    LINEMATE_DENSITY);
    init_pair(&world->_deraumere_info, world->_width, world->_height,
    DERAUMERE_DENSITY);
    init_pair(&world->_sibur_info, world->_width, world->_height,
    SIBUR_DENSITY);
    init_pair(&world->_mendiane_info, world->_width, world->_height,
    MENDIANE_DENSITY);
    init_pair(&world->_phiras_info, world->_width, world->_height,
    PHIRAS_DENSITY);
    init_pair(&world->_thystame_info, world->_width, world->_height,
    THYSTAME_DENSITY);
    amber_refill_world(world);
}

amber_world_t *amber_create_world(int width, int height, char **teams)
{
    amber_world_t *world = calloc(1, sizeof(amber_world_t));

    if (!world)
        return NULL;
    world->_width = width;
    world->_height = height;
    world->_case = calloc(height, sizeof(box_t *));
    for (int i = 0; i < height; i++) {
        world->_case[i] = calloc(width, sizeof(box_t));
        if (!world->_case[i])
            return NULL;
    }
    init_info_world(world);
    world->_eggs = create_list(amber_create_egg, amber_destroy_egg);
    for (int i = 0; teams[i]; i++)
        push_back_list(world->_eggs, world, RAND(width),
        RAND(height), teams[i], i);
    return world;
}

void destroy_amber_world(amber_world_t *world)
{
    if (!world)
        return;
    for (int i = 0; i < world->_height; i++)
        free(world->_case[i]);
    free(world->_case);
    free(world);
}

static void fill_box(box_t *box, amber_world_t *world)
{
    box->_food = world->_food_info._m_value - world->_food_info._c_value;
    box->_linemate = world->_linemate_info._m_value -
    world->_linemate_info._c_value;
    box->_deraumere = world->_deraumere_info._m_value -
    world->_deraumere_info._c_value;
    box->_sibur = world->_sibur_info._m_value - world->_sibur_info._c_value;
    box->_mendiane = world->_mendiane_info._m_value -
    world->_mendiane_info._c_value;
    box->_phiras = world->_phiras_info._m_value - world->_phiras_info._c_value;
    box->_thystame = world->_thystame_info._m_value -
    world->_thystame_info._c_value;
    world->_food_info._c_value = world->_food_info._m_value;
    world->_linemate_info._c_value = world->_linemate_info._m_value;
    world->_deraumere_info._c_value = world->_deraumere_info._m_value;
    world->_sibur_info._c_value = world->_sibur_info._m_value;
    world->_mendiane_info._c_value = world->_mendiane_info._m_value;
    world->_phiras_info._c_value = world->_phiras_info._m_value;
    world->_thystame_info._c_value = world->_thystame_info._m_value;
}

void amber_refill_world(amber_world_t *world)
{
    box_t box = {0};

    fill_box(&box, world);
    for (int i = 0; box._food > i; i++)
        world->_case[RAND(world->_height)][RAND(world->_width)]._food++;
    for (int i = 0; box._linemate > i; i++)
        world->_case[RAND(world->_height)][RAND(world->_width)]._linemate++;
    for (int i = 0; box._deraumere > i; i++)
        world->_case[RAND(world->_height)][RAND(world->_width)]._deraumere++;
    for (int i = 0; box._sibur > i; i++)
        world->_case[RAND(world->_height)][RAND(world->_width)]._sibur++;
    for (int i = 0; box._mendiane > i; i++)
        world->_case[RAND(world->_height)][RAND(world->_width)]._mendiane++;
    for (int i = 0; box._phiras > i; i++)
        world->_case[RAND(world->_height)][RAND(world->_width)]._phiras++;
    for (int i = 0; box._thystame > i; i++)
        world->_case[RAND(world->_height)][RAND(world->_width)]._thystame++;
}

static void display_box(amber_world_t *world)
{
    for (int i = 0; i < world->_height; i++) {
        for (int j = 0; j < world->_width; j++) {
            printf("=============Case[%d][%d]:\n", i, j);
            printf("Food: %d\n", world->_case[i][j]._food);
            printf("Linemate: %d\n", world->_case[i][j]._linemate);
            printf("Deraumere: %d\n", world->_case[i][j]._deraumere);
            printf("Sibur: %d\n", world->_case[i][j]._sibur);
            printf("Mendiane: %d\n", world->_case[i][j]._mendiane);
            printf("Phiras: %d\n", world->_case[i][j]._phiras);
            printf("Thystame: %d\n", world->_case[i][j]._thystame);
            printf("Players: %d\n", world->_case[i][j]._players);
            printf("Eggs: %d\n\n", world->_case[i][j]._eggs);
        }
    }
}

static void display_more(amber_world_t *world, bool box)
{
    printf("Eggs: %ld\n", list_len(world->_eggs));
    if (box)
        display_box(world);
}

void amber_display_world(amber_world_t *world, bool box)
{
    printf("=============AMBER WORLD=============\n");
    printf("Width: %d\n", world->_width);
    printf("Height: %d\n", world->_height);
    printf("Food: %d/%d\n", world->_food_info._c_value,
    world->_food_info._m_value);
    printf("Linemate: %d/%d\n", world->_linemate_info._c_value,
    world->_linemate_info._m_value);
    printf("Deraumere: %d/%d\n", world->_deraumere_info._c_value,
    world->_deraumere_info._m_value);
    printf("Sibur: %d/%d\n", world->_sibur_info._c_value,
    world->_sibur_info._m_value);
    printf("Mendiane: %d/%d\n", world->_mendiane_info._c_value,
    world->_mendiane_info._m_value);
    printf("Phiras: %d/%d\n", world->_phiras_info._c_value,
    world->_phiras_info._m_value);
    printf("Thystame: %d/%d\n", world->_thystame_info._c_value,
    world->_thystame_info._m_value);
    display_more(world, box);
    printf("=====================================\n");
}
