/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Clear the framebuffer.
*/
#include "wolf.h"
#include "../../render.h"

static void fill_sky(player_t *player)
{
    float t;
    int i;

    for (int y = 0; y < player->param.size.y; y++) {
        t = (float)y / player->param.size.y;
        for (int x = 0; x < player->param.size.x; x++) {
            i = (y * player->param.size.x + x) * 4;
            player->framebuffer[i + 0] = (1 - t) * 60 + t * 255;
            player->framebuffer[i + 1] = (1 - t) * 40 + t * 170;
            player->framebuffer[i + 2] = (1 - t) * 100 + t * 80;
            player->framebuffer[i + 3] = 255;
        }
    }
}

static void fill_floor(player_t *player)
{
    int width = player->param.size.x;
    int height = player->param.size.y;
    float darkness;
    float t;
    int i;

    for (int y = height / 2; y < height; y++) {
        t = (float)(height - 1 - y) / (height / 2);
        darkness = 1.0f - 0.4f * t;
        for (int x = 0; x < width; x++) {
            i = (y * width + x) * 4;
            player->framebuffer[i + 0] = 90 * darkness;
            player->framebuffer[i + 1] = 71 * darkness;
            player->framebuffer[i + 2] = 50 * darkness;
            player->framebuffer[i + 3] = 255;
        }
    }
}

/* Framebuffer is an sfUint8 * */
void clear_framebuffer(player_t *player)
{
    if (!player || !player->framebuffer) {
        return;
    }
    fill_sky(player);
    fill_floor(player);
    for (int i = 0; i < player->param.size.x * player->param.size.y; i++) {
        player->zbuffer[i] = TMP_CHN;
    }
    return;
}
