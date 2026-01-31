/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Draw minimap
*/
#include "wolf.h"
#include "../../../render.h"

const int map_radius = 70;  // 80 -> diameter
const sfVector2f map_center = (sfVector2f){640 - 80, 80};
const int map_raidus_show = 600;

static void draw_line_sp(player_t *player, sfVector4i_t ab, sfColor color, sfVector2f df)
{
    int dx = abs(ab.w - ab.x);
    int dy = abs(ab.h - ab.y);
    int sx = (ab.x < ab.w) ? 1 : -1;
    int sy = (ab.y < ab.h) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        if ((ab.x - map_center.x) * (ab.x - map_center.x) + (ab.y - map_center.y) * (ab.y - map_center.y) <= map_radius * map_radius) {
            put_pixel(player, (sfVector2i){ab.x, ab.y}, color, df);
        }
        if (ab.x == ab.w && ab.y == ab.h)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; ab.x += sx; }
        if (e2 < dx)  { err += dx; ab.y += sy; }
    }
}

sfVector2f toMinimap(sfVector2f worldPos, sfVector2f player, double player_angle)
{
    sfVector2f delta = {worldPos.x - player.x, worldPos.y - player.y};
    sfVector2f rot;
    sfVector2f minimap;

    rot.x = delta.x * -cos(-player_angle) - delta.y * -sin(-player_angle);
    rot.y = delta.x * -sin(-player_angle) + delta.y * -cos(-player_angle);
    minimap.x = map_center.x + (rot.x / map_raidus_show) * map_radius;
    minimap.y = map_center.y + (rot.y / map_raidus_show) * map_radius;
    return minimap;
}

static void draw_walls(bst_context_t *context, player_t *self)
{
    sfVector2f a = {0, 0};
    sfVector2f b = {0, 0};

    for (int i = 0; i < context->cmap->n_wall; i++) {
        a = toMinimap(context->cmap->walls[i].a, (sfVector2f){*self->x, *self->y}, *self->angle);
        b = toMinimap(context->cmap->walls[i].b, (sfVector2f){*self->x, *self->y}, *self->angle);
        draw_line_sp(self, (sfVector4i_t){a.x, a.y, b.x, b.y}, sfBlack, (sfVector2f){UX_CHN, 0});        
    }
}

static void draw_allies_m(bst_context_t *context, player_t *self)
{
    sfVector2f pos = {0, 0};

    for (int i = 0; i < context->n_players; i++) {
        if (context->players[i] == self) {
            continue;
        }
        if (context->players[i]->equipe == self->equipe) {
            pos = toMinimap((sfVector2f){*context->players[i]->x, *context->players[i]->y}, (sfVector2f){*self->x, *self->y}, *self->angle);
            if (get_norme(*context->players[i]->x, *context->players[i]->y, *self->x, *self->y) <= map_raidus_show)
                draw_circle(self, (sfVector4i_t){pos.x, pos.y, 5, 0}, UX_CHN, sfColor_fromRGB(43, 255, 255));
        }
    }
    return;
}

static void draw_heal_points(bst_context_t *context, player_t *self)
{
    sfVector2f pos = {0, 0};

    for (heals_t *temp = context->cmap->heals; temp; temp = temp->next) {
        if (!temp->is_taken && get_norme(*self->x, *self->y, temp->pos.x, temp->pos.y) <= map_raidus_show) {
            pos = toMinimap(temp->pos, (sfVector2f){*self->x, *self->y}, *self->angle);
            draw_circle(self, (sfVector4i_t){pos.x, pos.y, 2, 0}, UX_CHN, sfGreen);
        }
    }
}

static void draw_points(bst_context_t *context, player_t *self)
{
    sfVector2f pos1;
    char c = 'A';
    char buffer[8] = {};

    if (context->mode != BS_GO && context->mode == RANKED) {
        return;
    }
    for (bsp_t *temp = context->cmap->bsp; temp; temp = temp->next) {
        pos1 = toMinimap(temp->center, (sfVector2f){*self->x, *self->y}, *self->angle);
        if (get_norme(pos1.x, pos1.y, map_center.x, map_center.y) <= map_radius) {
            sprintf(buffer, "%c", c);
            draw_text(self, buffer, (sfVector4i_t){pos1.x, pos1.y, 2, UX_CHN}, sfRed);
        }
        c++;
    }
}

static void draw_blacksheep_minimap(bst_context_t *context, player_t *self)
{
    sfVector2f pos = {0, 0};

    if (context->mode != BS_GO && context->mode != RANKED) {
        return;
    }
    if (context->bs->is_carried || context->bs->is_fired) {
        return;
    }
    pos = toMinimap(context->bs->pos, (sfVector2f){*self->x, *self->y}, *self->angle);
    if (get_norme(pos.x, pos.y, map_center.x, map_center.y) <= map_radius) {
        draw_circle(self, (sfVector4i_t){pos.x, pos.y, 5, 0}, UX_CHN, sfBlack);
    }
}

void draw_minimap(bst_context_t *context, player_t *self)
{
    // Please refactor all of this file :pray::pray:

    draw_circle(self, (sfVector4i_t){map_center.x, map_center.y, map_radius, 0}, UX_CHN, sfColor_fromRGB(150, 150, 150));
    draw_walls(context, self);
    draw_heal_points(context, self);
    draw_allies_m(context, self);
    draw_points(context, self);
    draw_blacksheep_minimap(context, self);
    draw_circle(self, (sfVector4i_t){map_center.x, map_center.y, 5, 0}, UX_CHN, sfYellow);
}
