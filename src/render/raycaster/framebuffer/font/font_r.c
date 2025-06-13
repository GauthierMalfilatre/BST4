/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Font file
*/
#include "wolf.h"
#include "wolf_font.h"

void draw_letter_r(player_t *player, sfVector2i xy, sfVector2i scale_ch,
    sfColor color)
{
    draw_rect(player, (sfVector4i_t){xy.x, xy.y, scale_ch.x, scale_ch.x * 5},
        color, scale_ch.y);
    draw_rect(player, (sfVector4i_t){xy.x, xy.y, scale_ch.x * 3, scale_ch.x},
        color, scale_ch.y);
    draw_rect(player, (sfVector4i_t){xy.x, xy.y + scale_ch.x * 2,
        scale_ch.x * 2, scale_ch.x}, color, scale_ch.y);
    draw_rect(player, (sfVector4i_t){xy.x + scale_ch.x * 2, xy.y +
        scale_ch.x * 3, scale_ch.x, scale_ch.x * 2}, color, scale_ch.y);
    draw_rect(player, (sfVector4i_t){xy.x + scale_ch.x * 2, xy.y +
        scale_ch.x * 1, scale_ch.x, scale_ch.x}, color, scale_ch.y);
}
