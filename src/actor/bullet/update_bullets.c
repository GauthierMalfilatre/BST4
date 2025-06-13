/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for context engine v4.
** Movement of players
*/
#include "wolf.h"
#include <math.h>

static int is_collision_with_player(player_t *player, bullet_t *bullet,
    double delt_t)
{
    float radius = player->hitbox_radius + 10;
    sfVector2f dxy = {bullet->pos.x - *player->x, bullet->pos.y - *player->y};
    float dist_sq = dxy.x * dxy.x + dxy.y * dxy.y;
    sfVector2f fpos = {bullet->pos.x + bullet->dir.x * delt_t,
        bullet->pos.y + bullet->dir.y * delt_t};
    sfVector2f d = {fpos.x - bullet->pos.x, fpos.y - bullet->pos.y};
    sfVector2f f = {bullet->pos.x - *player->x, bullet->pos.y - *player->y};
    float a = d.x * d.x + d.y * d.y;
    float b = 2 * (f.x * d.x + f.y * d.y);
    float c = (f.x * f.x + f.y * f.y) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    float sqrt_disc = 0;
    sfVector2f t12;

    if (dist_sq <= radius * radius || discriminant < 0)
        return (discriminant < 0) ? 0 : 1;
    sqrt_disc = sqrtf(discriminant);
    t12.x = (-b - sqrt_disc) / (2 * a);
    t12.y = (-b + sqrt_disc) / (2 * a);
    return (t12.x >= 0 && t12.x <= 1) || (t12.y >= 0 && t12.y <= 1);
}

static int wall_callision(wolf_context_t *context, sfVector2f base,
    sfVector2f target, int dmg)
{
    sfVector2f inter = {NAN, NAN};

    for (int i = 0; i < context->cmap->n_wall; i++) {
        if (!get_intersect(&context->cmap->walls[i], base, target, &inter)) {
            remove_wall(&context->cmap->walls, &context->cmap->n_wall, i, dmg);
            return ERROR;
        }
    }
    return OK;
}

static void update_single_bullet(wolf_context_t *context, bullet_t *bullet)
{
    float delt_t = sfTime_asMicroseconds(sfClock_restart(bullet->clock)) / 200;

    for (int i = 0; i < context->n_players; i++) {
        if (context->players[i] == bullet->player || !bullet->player ||
            context->players[i]->infos.life <= 0.f)
            continue;
        if (is_collision_with_player(context->players[i], bullet, delt_t)) {
            deal_damage_to_player(context, context->players[i],
                bullet->player);
            destroy_bullet(&context->cmap->bullets, bullet);
            return;
        }
    }
    if (wall_callision(context, bullet->pos, (sfVector2f){bullet->pos.x +
        bullet->dir.x * delt_t, bullet->pos.y + bullet->dir.y * delt_t},
        bullet->player->character->atk)) {
        destroy_bullet(&context->cmap->bullets, bullet);
        return;
    }
    bullet->pos.x += bullet->dir.x * delt_t;
    bullet->pos.y += bullet->dir.y * delt_t;
}

void udpdate_bullets(wolf_context_t *context)
{
    bullet_t *temp = context->cmap->bullets;
    bullet_t *next = NULL;
    bullet_t *current = NULL;

    while (temp) {
        next = temp->next;
        current = temp;
        temp = next;
        update_single_bullet(context, current);
    }
}
