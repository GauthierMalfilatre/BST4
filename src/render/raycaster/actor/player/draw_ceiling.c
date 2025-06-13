/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for wolf3D
*/
#include "wolf.h"
#include "../../../render.h"
#include <math.h>

static floor_dirs_t compute_dirs(float angle, float fov)
{
    floor_dirs_t d;

    d.dir_x0 = cosf(angle - fov / 2.0f);
    d.dir_y0 = sinf(angle - fov / 2.0f);
    d.dir_x1 = cosf(angle + fov / 2.0f);
    d.dir_y1 = sinf(angle + fov / 2.0f);
    return d;
}

static void draw_ceiling_pixels(floor_ctx_t *ctx,
    floor_step_t *step, int y)
{
    int x;
    int tx;
    int ty;

    for (x = 0; x < ctx->width; x++) {
        tx = ((int)(fabsf(step->floor_x) * ctx->tex->width)) %
            ctx->tex->width;
        ty = ((int)(fabsf(step->floor_y) * ctx->tex->height)) %
            ctx->tex->height;
        put_pixel(ctx->player, (sfVector2i){x, y},
            sfImage_getPixel(ctx->tex->image, tx, ty),
            (sfVector2f){-1.f, 0});
        step->floor_x += step->step_x;
        step->floor_y += step->step_y;
    }
}

static void render_ceiling_line(floor_ctx_t *ctx, int y, player_t *player)
{
    float fov;
    float pos_z;
    int p;
    float row_dist;
    floor_step_t step;
    int horizon = ctx->height / 2;

    fov = ctx->player->param.fov;
    pos_z = ((float)ctx->width / 2.0f) / tanf(fov / 2.0f);
    p = horizon - y;
    if (p == 0)
        return;
    row_dist = pos_z / (float)p;
    step.floor_x = *player->x + row_dist * ctx->dirs->dir_x0;
    step.floor_y = *player->y + row_dist * ctx->dirs->dir_y0;
    step.step_x = row_dist * (ctx->dirs->dir_x1 - ctx->dirs->dir_x0) /
        (float)ctx->width;
    step.step_y = row_dist * (ctx->dirs->dir_y1 - ctx->dirs->dir_y0) /
        (float)ctx->width;
    draw_ceiling_pixels(ctx, &step, y);
}

void render_ceiling(player_t *player, sfVector2i screen, wolf_context_t *ctx)
{
    tex_info_t tex;
    floor_dirs_t dirs;
    floor_ctx_t ceil;

    if (!ctx->cmap || !ctx->cmap->ceiling)
        return;
    tex.image = ctx->cmap->ceiling->image;
    if (!tex.image)
        return;
    tex.width = sfImage_getSize(tex.image).x;
    tex.height = sfImage_getSize(tex.image).y;
    dirs = compute_dirs(*player->angle, player->param.fov);
    ceil.player = player;
    ceil.tex = &tex;
    ceil.dirs = &dirs;
    ceil.width = screen.x;
    ceil.height = screen.y;
    for (int y = 0; y < screen.y / 2; y++)
        render_ceiling_line(&ceil, y, player);
}
