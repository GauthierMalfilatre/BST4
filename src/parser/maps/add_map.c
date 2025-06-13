/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

int add_map_p(char **warray, wolf_context_t *context)
{
    if (my_len_word_array(warray) < 2) {
        return ERROR;
    }
    context->n_map++;
    context->maps = realloc(context->maps, sizeof(maps_t *) * context->n_map);
    context->maps[context->n_map - 1] = create_map(warray[1]);
    return OK;
}
