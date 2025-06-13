/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

int add_hp_p(char **warray, wolf_context_t *context)
{
    if (my_len_word_array(warray) < 3 || !context->n_map) {
        return ERROR;
    }
    add_heal_point(&context->maps[context->n_map - 1]->heals,
        (sfVector2f){atof(warray[1]), atof(warray[2])});
    return OK;
}
