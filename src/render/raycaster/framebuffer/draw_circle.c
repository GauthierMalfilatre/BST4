/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Put a pixel in the framebuffer regarding the zbuffer.
*/
#include "wolf.h"
#include "../../render.h"


void draw_circle(player_t *player, sfVector4i_t centerr, int chan,
    sfColor color)
{
    int diameter = centerr.w * 2 + 1;
    int area = diameter * diameter;
    sfVector2i pixel;
    int x = 0;
    int y = 0;

    for (int i = 0; i < area; i++) {
        x = (i % diameter) - centerr.w;
        y = (i / diameter) - centerr.w;
        if (x * x + y * y <= centerr.w * centerr.w) {
            pixel = (sfVector2i){centerr.x + x, centerr.y + y};
            put_pixel(player, pixel, color, (sfVector2f){chan, 1});
        }
    }
}
