/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Move gestion for bst scene.
*/
#include "wolf.h"
#include "sound.h"

void drop_blacksheep(wolf_context_t *context)
{
    blacksheep_t *bs = context->bs;

    if (context->mode != BS_GO || !bs->is_carried) {
        return;
    }
    bs->pos.x = *bs->is_carried->x;
    bs->pos.y = *bs->is_carried->y;
    printf("Player %s (%p) has dropped the blacksheep\n",
        bs->is_carried->name, bs->is_carried);
    bs->is_carried = 0;
    if (!bs->is_fired) {
        bs->firing = 0.f;
        play_if_exists(context->w_sound.sounds, "__bs_dropped");
    }
    return;
}
