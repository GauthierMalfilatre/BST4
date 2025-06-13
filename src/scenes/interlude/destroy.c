/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy bst scene.
*/
#include "wolf.h"
#include "../../render/render.h"

void interlude_destroy(wolf_context_t *context)
{
    if (!context || !context->interlude)
        return;
    if (context->interlude->rect)
        sfRectangleShape_destroy(context->interlude->rect);
    if (context->interlude->text)
        sfText_destroy(context->interlude->text);
    if (context->interlude->sprite)
        sfSprite_destroy(context->interlude->sprite);
    if (context->interlude->clock)
        sfClock_destroy(context->interlude->clock);
    if (!context->interlude->font)
        sfFont_destroy(context->interlude->font);
    free(context->interlude);
    context->interlude = NULL;
}
