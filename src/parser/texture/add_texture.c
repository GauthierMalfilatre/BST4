/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"

int add_texture_p(char **warray, wolf_context_t *context)
{
    if (my_len_word_array(warray) < 4) {
        return ERROR;
    }
    add_texture(&context->textures, warray[1], atoi(warray[3]), warray[2]);
    return OK;
}
