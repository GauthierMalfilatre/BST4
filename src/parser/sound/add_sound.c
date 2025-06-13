/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include "sound.h"
#include <string.h>

int add_sound_p(char **warray, wolf_context_t *context)
{
    if (my_len_word_array(warray) < 3 || !context) {
        return ERROR;
    }
    if (add_sound(&context->w_sound.sounds, warray[1], warray[2]) == ERROR) {
        return ERROR;
    }
    return OK;
}
