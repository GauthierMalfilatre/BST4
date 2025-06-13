/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Create bst scene.
*/

#include "wolf.h"
#include "../../../render/render.h"

static void walls(wolf_context_t *context)
{
    if (context->bst->is_temp_wall) {
        context->bst->is_temp_wall = sfFalse;
        for (temp_wall_t *temp = context->cmap->temp_walls; temp; temp =
            temp->next) {
            remove_wall_at_index(&context->cmap->walls, &context->cmap->n_wall,
                temp->index);
            resolve_others_temp_wall_index(context->cmap->temp_walls,
                temp->index);
        }
    }    
}

void bst_destroy(wolf_context_t *context)
{
    if (!context->bst) {
        return;
    }
    if (context->bst->score_rect)
        sfRectangleShape_destroy(context->bst->score_rect);
    if (context->bst->bar_rect)
        sfRectangleShape_destroy(context->bst->bar_rect);
    if (context->bst->clock)
        sfClock_destroy(context->bst->clock);
    if (context->bst->text)
        sfText_destroy(context->bst->text);
    if (context->bst->font)
        sfFont_destroy(context->bst->font);
    walls(context);
    destroy_rain_list(context->bst->rain);
    destroy_render_multithread(context);
    free(context->bst);
    context->bst = NULL;
}
