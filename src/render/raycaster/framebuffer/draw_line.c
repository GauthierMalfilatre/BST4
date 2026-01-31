/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Clear the framebuffer.
*/
#include "wolf.h"
#include "../../render.h"

void draw_line(player_t *player, sfVector4i_t ab, sfColor color, sfVector2f df)
{
    int dx = abs(ab.w - ab.x);
    int dy = abs(ab.h - ab.y);
    int sx = (ab.x < ab.w) ? 1 : -1;
    int sy = (ab.y < ab.h) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        put_pixel(player, (sfVector2i){ab.x, ab.y}, color, df);
        if (ab.x == ab.w && ab.y == ab.h)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; ab.x += sx; }
        if (e2 < dx)  { err += dx; ab.y += sy; }
    }
}
