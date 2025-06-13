/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

blacksheep_t *create_blacksheep(wolf_context_t *context)
{
    blacksheep_t *bs;

    context->bs = malloc(sizeof(blacksheep_t));
    bs = context->bs;
    if (!bs) {
        return NULL;
    }
    bs->is_carried = (player_t *) 0;
    bs->is_fired = 0;
    bs->rect = (sfIntRect){0, 0, 128, 128};
    bs->texture = get_texture(context->textures, "__bs");
    bs->pos = (sfVector2f){0, 0};
    bs->clock = sfClock_create();
    bs->diffusing = (player_t *) 0;
    bs->firing = 0.f;
    if (!bs->texture) {
        free(bs);
        return NULL;
    }
    return bs;
}

int spawn_blacksheep(wolf_context_t *context)
{
    spawns_t *spawn = find_spawn_point(context->cmap->spawns, ATK);

    context->bs->pos.x = spawn->a.x + rand() % (int)(spawn->b.x - spawn->a.x);
    context->bs->pos.y = spawn->a.y + rand() % (int)(spawn->b.y - spawn->a.y);
    context->bs->diffusing = 0;
    context->bs->is_carried = 0;
    sfClock_restart(context->bs->clock);
    context->bs->is_fired = 0;
    context->bs->firing = 0;
    return OK;
}
