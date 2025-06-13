/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

int destroy_blacksheep(blacksheep_t *blacksheep)
{
    if (!blacksheep || !blacksheep->clock) {
        return ERROR;
    }
    sfClock_destroy(blacksheep->clock);
    free(blacksheep);
    return OK;
}
