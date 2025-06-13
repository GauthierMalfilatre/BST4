/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Clear the framebuffer.
*/
#include "wolf.h"
#include "../../render.h"

void draw_rect(player_t *player, sfVector4i_t xy, sfColor color, double depth)
{
    if (!player) {
        return;
    }
    for (int i = xy.y; i < xy.h + xy.y; i++) {
        for (int j = xy.x; j < xy.w + xy.x; j++) {
            put_pixel(player, (sfVector2i){j, i}, color,
                (sfVector2f) {depth, 0});
        }
    }
    return;
}
