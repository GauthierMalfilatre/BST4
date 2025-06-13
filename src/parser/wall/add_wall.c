/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Parse main file for configuration
*/
#include "wolf.h"

int add_wall(wall_t wall, maps_t *map)
{
    map->n_wall++;
    map->walls = realloc(map->walls, sizeof(wall_t) * map->n_wall);
    if (!map->walls) {
        return ERROR;
    }
    map->walls[map->n_wall - 1] = wall;
    return OK;
}

int add_wall_p(char **warray, wolf_context_t *context)
{
    if (my_len_word_array(warray) < 6 || context->n_map < 1) {
        return ERROR;
    }
    add_wall((wall_t){
        .a = (sfVector2f){atof(warray[1]), atof(warray[2])},
        .b = (sfVector2f){atof(warray[3]), atof(warray[4])},
        .type = my_getnbr(warray[5]),
        .is_breakable = 0,
        .alpha = 1.f,
        .builder = (player_t *) 0}, context->maps[context->n_map - 1]);
    return OK;
}
