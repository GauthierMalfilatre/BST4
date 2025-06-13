/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../../render.h"
#include "scenes.h"

void draw_blacksheep_ui(player_t *player, wolf_context_t *context)
{
    if (context->bs && context->bs->is_carried == player) {
        draw_sprite_x_y_2d((sfVector2f){-30, 200}, player, 2.f,
            (sfIntRect_text_t){context->bs->rect, context->bs->texture});
    }
    if (!player->equipe && context->bs->is_carried == player &&
        is_in_bsp(player, context->cmap->bsp) && !context->bs->firing) {
        draw_text(player, "4 to fire the sheep", (sfVector4i_t)
            {320 - (20 / 2) * 5 * 3, 480 - 140, 3, UX_CHN}, sfRed);
    }
    if (player->equipe == 1 && context->bs->is_fired && !context->bs->diffusing
        && get_norme(*player->x, *player->y, context->bs->pos.x,
        context->bs->pos.y) <= 100.f) {
        draw_text(player, "4 to defire the sheep", (sfVector4i_t)
            {320 - (22 / 2) * 5 * 3, 480 - 140, 3, UX_CHN}, sfRed);
    }
}
