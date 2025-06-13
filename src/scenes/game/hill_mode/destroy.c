/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Create bst scene.
*/

#include "wolf.h"
#include "../../../render/render.h"

void hill_destroy(wolf_context_t *context)
{
    if (!context->hill) {
        return;
    }
    if (context->hill->score_rect)
        sfRectangleShape_destroy(context->hill->score_rect);
    if (context->hill->bar_rect)
        sfRectangleShape_destroy(context->hill->bar_rect);
    if (context->hill->clock)
        sfClock_destroy(context->hill->clock);
    if (context->hill->text)
        sfText_destroy(context->hill->text);
    if (context->hill->font)
        sfFont_destroy(context->hill->font);
    destroy_rain_list(context->hill->rain);
    destroy_render_multithread(context);
    free(context->hill);
    context->hill = NULL;
}
