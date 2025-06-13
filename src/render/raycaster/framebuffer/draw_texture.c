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
    int src_x;
    int src_y;
    sfColor color;

    if (ctx.rect.left != -1) {
        if (x < ctx.rect.left || x >= ctx.rect.left + ctx.rect.width)
            return;
        if (y < ctx.rect.top || y >= ctx.rect.top + ctx.rect.height)
            return;
    }
    src_x = (x * ctx.param.img_size.x) / ctx.param.sprite_width;
    src_y = (y * ctx.param.img_size.y) / ctx.param.sprite_height;
    color = sfImage_getPixel(ctx.image, src_x, src_y);
    put_pixel_if_not_alpha(ctx.player,
        (sfVector2i){ctx.param.x_start + x, ctx.param.y_start + y},
        color, ctx.param.depth);
}

static void draw_sprite_sub(player_t *player, draw_sprite_param_t param,
    sfImage *image, sfIntRect rect)
{
    draw_pixel_ctx_t ctx = {player, param, image, rect};

    for (int y = param.y_min; y < param.y_max; y++) {
        for (int x = param.x_min; x < param.x_max; x++) {
            draw_sprite_pixel(ctx, x, y);
        }
    }
}

static sfVector2i find_size(double depth, sfVector2i size, sfVector2u img_size)
{
    int sprite_height = (size.y * 100) / (depth + 0.0001);
    int sprite_width = (img_size.x * sprite_height) / img_size.y;

    if (depth == UX_CHN || depth == SELF_CHN) {
        sprite_height = img_size.y;
        sprite_width = img_size.x;
    }
    return (sfVector2i) {sprite_width, sprite_height};
}

static int find_xmax(int draw_width, sfIntRect rect, sfVector2u img_size,
    sfVector2f xdp)
{
    int crop_width = draw_width;
    int crop_left = 0;

    if (rect.left != -1) {
        crop_left = (rect.left * draw_width) / img_size.x;
        crop_width = (rect.width * draw_width) / img_size.x;
    }
    return xdp.x - crop_width / 2 - crop_left;
}

void draw_sprite(sfVector2f xdp, player_t *player, textures_t *target,
    sfIntRect rect)
{
    sfVector2u img_size = sfImage_getSize(target->image);
    int screen_w = player->param.size.x;
    int screen_h = player->param.size.y;
    sfVector2i sprite_s = find_size(xdp.y, player->param.size, img_size);
    int y_start = screen_h / 2 - sprite_s.y / 2;
    int draw_width = sprite_s.x;
    int x_start = find_xmax(draw_width, rect, img_size, xdp);
    int y_min = y_start < 0 ? -y_start : 0;
    int y_max = sprite_s.y;
    int x_min = x_start < 0 ? -x_start : 0;
    int x_max = sprite_s.x;

    if (x_start + x_max > screen_w)
        x_max = screen_w - x_start;
    if (y_start + y_max > screen_h)
        y_max = screen_h - y_start;
    draw_sprite_sub(player, (draw_sprite_param_t){y_min, y_max, x_min, x_max,
        xdp.y, sprite_s.x, sprite_s.y, x_start, y_start, img_size},
        target->image, rect);
}

static void draw_pixel_scaled_from_index(player_t *player, sfVector2f pos,
    sfVector2i iscale, sfIntRect_text_t recttext)
{
    int i = iscale.x;
    int scale = iscale.y;
    int width_scaled = recttext.rect.width * scale;
    int x_dest = i % width_scaled;
    int y_dest = i / width_scaled;
    int x_src = x_dest / scale;
    int y_src = y_dest / scale;
    sfVector2i tex = {recttext.rect.left + x_src, recttext.rect.top + y_src};
    sfColor color = sfImage_getPixel(recttext.text->image, tex.x, tex.y);
    sfVector2i pixel = {(int)pos.x + x_dest, (int)pos.y + y_dest};

    if (color.a == 0)
        return;
    put_pixel(player, pixel, color, (sfVector2f){UX_CHN, 0});
}

void draw_sprite_x_y_2d(sfVector2f pos, player_t *player,
    float scale_f, sfIntRect_text_t recttext)
{
    int scale = (int)scale_f;
    int width_scaled = recttext.rect.width * scale;
    int height_scaled = recttext.rect.height * scale;
    int area = width_scaled * height_scaled;

    for (int i = 0; i < area; i++)
        draw_pixel_scaled_from_index(player, pos, (sfVector2i){i, scale},
            recttext);
}
