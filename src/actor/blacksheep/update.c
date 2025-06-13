/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Move gestion for bst scene.
*/
#include "wolf.h"

void update_blacksheep(wolf_context_t *context)
{
    blacksheep_t *bs = context->bs;

    if (context->mode != BS_GO || bs->is_carried) {
        return;
    }
    bs->rect.left = 128 * (int)fmod((sfTime_asSeconds(
        sfClock_getElapsedTime(bs->clock)) / 0.5), 2.f)
        + 128 * 2 * (bs->is_fired);
    return;
}
