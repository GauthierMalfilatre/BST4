/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../render.h"
#include "../../../../textures/textures.h"

static sfBool is_any_alpha(wolf_context_t *ctx, wall_t wall)
{
    sfImage *img;
    const sfUint8 *pixels;
    sfVector2u size;
    textures_t *texture = get_texture_from_type(ctx->textures, wall.type);

    if (!texture || !texture->image)
        return sfFalse;
    img = texture->image;
    pixels = sfImage_getPixelsPtr(img);
    size = sfImage_getSize(img);
    for (unsigned int i = 0; i < size.x * size.y; i++) {
        if (pixels[i * 4 + 3] < 200) {
            return sfTrue;
        }
    }
    return sfFalse;
}

static void rec_alpha(wolf_context_t *ray, player_t *player,
    float angle, raycaster_param_t p)
{
    if (ray->cmap->walls[p.i].alpha != 1.f) {
        cast_ray(ray, player, angle, (raycaster_param_t)
            {p.rays, (sfVector2f){p.base_pos.x -1 * sin(angle) * 10.f,
            p.base_pos.y + cos(angle) * 10.f}, p.target_pos, 0});
    }
}

void cast_ray(wolf_context_t *ray, player_t *player, float angle,
    raycaster_param_t p)
{
    sfVector2f collision = {0.0 / 0.0, 0.0 / 0.0};
    int wall = 0;
    double depth = 0;

    for (int i = 0; i < ray->cmap->n_wall; i++) {
        if (get_intersect(&ray->cmap->walls[i], p.base_pos, p.target_pos,
            &collision) == OK) {
            wall = i;
            rec_alpha(ray, player, angle, (raycaster_param_t)
                {p.rays, collision, p.target_pos, i});
        }
    }
    depth = get_norme(*player->x, *player->y, collision.x, collision.y);
    if (!isnan(collision.x)) {
        draw_wall(ray, player, (cast_ray_params_t)
            {p.rays, depth, angle, collision, ray->cmap->walls[wall]});
    }
    return;
}

void raycaster(wolf_context_t *context, player_t *player)
{
    float screen_center = player->param.size.x / 2.0f;
    float ray_angle = 0;

    render_floor(player, player->param.size, context);
    render_ceiling(player, player->param.size, context);
    for (int i = 0; i < player->param.casted_rays; i++) {
        ray_angle = *player->angle + atanf((i - screen_center) / screen_center
            * tanf(player->param.fov / 2));
        cast_ray(context, player, ray_angle, (raycaster_param_t){i,
        (sfVector2f){*player->x, *player->y}, (sfVector2f){*player->x + -1 *
            sin(ray_angle) * 1e6, *player->y + cos(ray_angle) * 1e6}, 0});
    }
}
