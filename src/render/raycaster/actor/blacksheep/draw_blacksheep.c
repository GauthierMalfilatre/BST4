/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Draw players sprite
*/
#include "wolf.h"
#include "../../../render.h"

void draw_blacksheep(wolf_context_t *context, player_t *player)
{
    int x_out;
    double depth_out;
    blacksheep_t *bs = context->bs;

    if (context->mode != BS_GO || bs->is_carried) {
        return;
    }
    if (project_stuff_on_screen(player, bs->pos, &x_out, &depth_out) &&
        get_norme(*player->x, *player->y, bs->pos.x, bs->pos.y) >= 50) {
        draw_sprite_cropped((sfVector2f){x_out, depth_out}, player,
            bs->texture, bs->rect);
    }
}
