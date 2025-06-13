/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../render.h"
#include "scenes.h"
#include "../../framebuffer/font/wolf_font.h"

static void draw_action_bar(player_t *player, wolf_context_t *context)
{
    char buffer[32];

    if (context->bs->is_carried == player && context->bs->firing) {
        sprintf(buffer, "%.2f", (FIRE_TIME - context->bs->firing) / 1000.f);
        draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100,
            player->param.size.y - 100, (200) *
            (context->bs->firing / 40.f * 1 / 100), 12}, sfWhite, UX_CHN);
        draw_text(player, buffer, (sfVector4i_t){player->param.size.x / 2 - 10,
            player->param.size.y - 130, 5, UX_CHN}, sfWhite);
    }
    if (context->bs->diffusing == player && context->bs->is_fired) {
        sprintf(buffer, "%.2f", (context->bs->firing) / 1000.f);
        draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100,
            player->param.size.y - 100, (200) * ((4000.f -
            context->bs->firing) / 40.f * 1 / 100), 12}, sfWhite, UX_CHN);
        draw_text(player, buffer, (sfVector4i_t){player->param.size.x / 2 - 10,
                player->param.size.y - 130, 5, UX_CHN}, sfWhite);        
        }
}

void draw_ui(wolf_context_t *context, player_t *player)
{
    draw_cursor(player);
    draw_hps(player);
    draw_action_bar(player, context);
    draw_ammo(player);
    draw_skill(player);
    render_messages(player);
    if (context->current_scene != GAME_BST_SCENE)
        return;
    draw_rain_drops(context->bst->rain, player, player->delta_t);
    draw_blacksheep_ui(player, context);
    draw_directions(context, player);
}
