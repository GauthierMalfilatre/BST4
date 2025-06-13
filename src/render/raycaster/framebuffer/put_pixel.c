/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Put a pixel in the framebuffer regarding the zbuffer.
*/

#include "wolf.h"
#include "../../render.h"

static sfColor get_color_from_framebuffer(sfUint8 *framebuffer, const int i)
{
    return (sfColor){framebuffer[i], framebuffer[i + 1], framebuffer[i + 2],
        framebuffer[i + 3]};
}

static void put_pixel_sub(player_t *player, sfColor new_color, int i,
    float depth)
{
    float attenuation = 1.0f / (1.0f + 0.002f * depth);

    if (depth == UX_CHN || depth == SELF_CHN) {
        attenuation = 1.f;
    }
    new_color.r *= attenuation;
    new_color.g *= attenuation;
    new_color.b *= attenuation;
    player->framebuffer[i + 0] = new_color.r;
    player->framebuffer[i + 1] = new_color.g;
    player->framebuffer[i + 2] = new_color.b;
    player->framebuffer[i + 3] = new_color.a;
}

void put_pixel(player_t *player, sfVector2i xy, sfColor color, sfVector2f df)
{
    double depth = df.x;
    int i;
    int x = xy.x;
    int y = xy.y;
    sfColor new_color = color;

    if (x < 0 || y < 0 ||
        x >= player->param.size.x || y >= player->param.size.y)
        return;
    if (player->zbuffer[y * player->param.size.x + x] <
        depth && player->zbuffer[y * player->param.size.x + x] != TMP_CHN) {
        return;
    }
    i = (y * player->param.size.x + x) * 4;
    if (df.y && color.a != 255) {
        new_color = blend_rgb332(get_color_from_framebuffer(
            player->framebuffer, i), new_color, df.y);
    }
    put_pixel_sub(player, new_color, i, depth);
    player->zbuffer[y * player->param.size.x + x] = depth;
}
