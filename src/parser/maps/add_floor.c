/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

int add_floor_p(char **warray, wolf_context_t *context)
{
    if (my_len_word_array(warray) < 2 || !context->n_map ||
        !context->textures) {
        return ERROR;
    }
    context->maps[context->n_map - 1]->ceiling = (textures_t *) 0;
    context->maps[context->n_map - 1]->floor
        = get_texture(context->textures, warray[1]);
    if (my_len_word_array(warray) >= 3)
        context->maps[context->n_map - 1]->ceiling
            = get_texture(context->textures, warray[2]);
    if (!context->maps[context->n_map - 1]->floor) {
        fprintf(stderr, PROGNAME": Failed to assign floor %s to map %s\n",
            warray[1], context->cmap->name);
        return ERROR;
    }
    return OK;
}
