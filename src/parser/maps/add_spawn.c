/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

int add_spawn_p(char **warray, wolf_context_t *context)
{
    if (my_len_word_array(warray) < 6 || !context->n_map) {
        return ERROR;
    }
    add_spawn_point(&context->maps[context->n_map - 1]->spawns,
        (sfVector2f){atof(warray[1]),
        atof(warray[2])}, (sfVector2f){atof(warray[3]), atof(warray[4])},
        atoi(warray[5]));
    return OK;
}
