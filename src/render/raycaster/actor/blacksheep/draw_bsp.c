/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Draw players sprite
*/
#include "wolf.h"
#include "../../../render.h"

void draw_bsps(wolf_context_t *context, player_t *player)
{
    int x_out;
    double depth_out;

    if (context->mode != BS_GO) {
        return;
    }
    for (bsp_t *bsp = context->cmap->bsp; bsp; bsp = bsp->next) {
        if (project_stuff_on_screen(player, bsp->center, &x_out, &depth_out) &&
            get_norme(*player->x, *player->y, bsp->center.x, bsp->center.y)
            >= 50.f) {
            draw_sprite((sfVector2f){x_out, depth_out}, player,
            get_texture(context->textures, "__bsp"), (sfIntRect){-1, 0, 0, 0});
        }
    }
}
