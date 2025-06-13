/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

character_t *get_character(wolf_context_t *context, const char *name)
{
    for (int i = 0; i < context->n_chars; i++) {
        if (!strcmp(context->characters[i]->name, name)) {
            return context->characters[i];
        }
    }
    return (character_t *) 0;
}
