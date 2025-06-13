/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Parse main file for configuration
*/
#include "wolf.h"

int add_stuff_p(char **warray, wolf_context_t *context)
{
    maps_t *map = 0;

    if (my_len_word_array(warray) < 4 || context->n_map < 1) {
        return ERROR;
    }
    map = context->maps[context->n_map - 1];
    add_stuff(&map->stuffs, (sfVector2f){atof(warray[1]), atof(warray[2])},
        atoi(warray[3]));
    return OK;
}
