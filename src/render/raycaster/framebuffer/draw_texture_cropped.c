/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Draw players sprite
*/
#include "wolf.h"
#include "../../render.h"

static void put_pixel_if_not_alpha(player_t *player, sfVector2i vect,
    sfColor color, double depth)
{
    if (color.a == 0)
        return;
    put_pixel(player, vect, color, (sfVector2f){depth, 0});
}

static void draw_sprite_pixel(draw_pixel_ctx_t ctx, int x, int y)
{
    int src_x = ctx.rect.left + (x * ctx.rect.width) / ctx.param.sprite_width;
    int src_y = ctx.rect.top + (y * ctx.rect.height) / ctx.param.sprite_height;
    sfVector2u img_size = sfImage_getSize(ctx.image);
    sfColor color;

    if (src_x < 0 || src_y < 0 || src_x >= (int)img_size.x || src_y >=
        (int)img_size.y)
        return;
    color = sfImage_getPixel(ctx.image, src_x, src_y);
    put_pixel_if_not_alpha(ctx.player,
        (sfVector2i){ctx.param.x_start + x, ctx.param.y_start + y},
        color, ctx.param.depth);
}

static void draw_sprite_cropped_sub(player_t *player,
    draw_sprite_param_t param, sfImage *image, sfIntRect rect)
{
    draw_pixel_ctx_t ctx = {player, param, image, rect};

    for (int y = param.y_min; y < param.y_max; y++) {
        for (int x = param.x_min; x < param.x_max; x++) {
            draw_sprite_pixel(ctx, x, y);
        }
    }
}

static sfVector2i find_cropped_size(double depth, sfVector2i screen_size,
    sfIntRect rect)
{
    int sprite_height = (screen_size.y * 100) / (depth + 0.0001);
    int sprite_width = (rect.width * sprite_height) / rect.height;

    return (sfVector2i){sprite_width, sprite_height};
}

void draw_sprite_cropped(sfVector2f xdp, player_t *player,
    textures_t *target, sfIntRect rect)
{
    int screen_w = player->param.size.x;
    int screen_h = player->param.size.y;
    sfVector2i sprite_s = find_cropped_size(xdp.y, player->param.size, rect);
    int y_start = screen_h / 2 - sprite_s.y / 2;
    int x_start = xdp.x - sprite_s.x / 2;
    int y_min = y_start < 0 ? -y_start : 0;
    int y_max = sprite_s.y;
    int x_min = x_start < 0 ? -x_start : 0;
    int x_max = sprite_s.x;

    if (x_start + x_max > screen_w)
        x_max = screen_w - x_start;
    if (y_start + y_max > screen_h)
        y_max = screen_h - y_start;
    draw_sprite_cropped_sub(player, (draw_sprite_param_t){
        y_min, y_max, x_min, x_max, xdp.y,
        sprite_s.x, sprite_s.y, x_start, y_start,
        (sfVector2u){rect.width, rect.height}
    }, target->image, rect);
}
