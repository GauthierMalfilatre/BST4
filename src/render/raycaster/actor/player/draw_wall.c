/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../render.h"

static int find_x(sfVector2f collision, wall_t wall, int wall_tex_w)
{
    float wall_dx = wall.b.x - wall.a.x;
    float wall_dy = wall.b.y - wall.a.y;
    float wall_length = sqrtf(wall_dx * wall_dx + wall_dy * wall_dy);
    float hit_dx = collision.x - wall.a.x;
    float hit_dy = collision.y - wall.a.y;
    float distance_on_wall = (hit_dx * wall_dx + hit_dy * wall_dy)
        / wall_length;
    int tex_x = ((int)(distance_on_wall)) % wall_tex_w;

    if (tex_x < 0)
        tex_x += wall_tex_w;
    return tex_x;
}

static sfImage *get_good_wall(wolf_context_t *ray, wall_t wall)
{
    return get_texture_from_type(ray->textures, wall.type)->image;
}

void draw_wall(wolf_context_t *ray, player_t *player, cast_ray_params_t p)
{
    sfImage *image = get_good_wall(ray, p.wall);
    int wall_heigth;
    int tex_x = find_x(p.collision, p.wall, sfImage_getSize(image).x);
    int draw_start;
    int draw_end;
    float tex_pos;
    int tex_y;

    p.depth *= cos(*player->angle - p.start_angle);
    wall_heigth = (player->param.size.y * 100) / (p.depth + 0.0001);
    draw_start = -wall_heigth / 2 + player->param.size.y / 2;
    draw_end = wall_heigth / 2 + player->param.size.y / 2;
    for (int y = draw_start & ~(draw_start >> 31); y < draw_end &&
        y < player->param.size.y; y++) {
        tex_pos = (y - draw_start) / (float)wall_heigth;
        tex_y = (int)(tex_pos * sfImage_getSize(image).y);
        put_pixel(player, (sfVector2i){player->param.size.x /
            player->param.casted_rays * p.rays, y},
            sfImage_getPixel(image, tex_x, tex_y), (sfVector2f){p.depth,
            p.wall.alpha});
    }
}
