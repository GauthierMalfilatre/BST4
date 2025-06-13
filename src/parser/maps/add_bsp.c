/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

int add_bsp_p(char **warray, wolf_context_t *context)
{
    if (my_len_word_array(warray) < 5 || !context->n_map) {
        return ERROR;
    }
    add_bsp(&context->maps[context->n_map - 1]->bsp,
        (sfVector2f){atof(warray[1]),
        atof(warray[2])}, (sfVector2f){atof(warray[3]), atof(warray[4])});
    return OK;
}
