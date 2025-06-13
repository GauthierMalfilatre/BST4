/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../render.h"
#include "framebuffer/font/wolf_font.h"

static void draw_self(wolf_context_t *context, player_t *player)
{
    (void) context;
    draw_sprite((sfVector2f){player->param.size.x / 2, UX_CHN}, player,
        player->character->self, player->utils->self_rect);
}

void player_render(wolf_context_t *context, player_t *player)
{
    clear_framebuffer(player);
    raycaster(context, player);
    draw_mob(context, player);
    draw_blacksheep(context, player);
    draw_bsps(context, player);
    draw_stuffs(context, player);
    draw_bullets(context, player);
    draw_heals(context, player);
    draw_self(context, player);
    draw_ui(context, player);
}

static void player_draw(wolf_context_t *context, player_t *player)
{
    if (!player->utils || !player->utils->render_texture) {
        return;
    }
    sfTexture_updateFromPixels(player->utils->render_texture,
        player->infos.life <= 0.f && player->killer ? player->killer->
        framebuffer : player->framebuffer,
        player->param.size.x, player->param.size.y, 0, 0);
    sfRenderWindow_drawSprite(context->view->window,
        player->utils->render_sprite, NULL);
    if (player->infos.life <= 0.f)
        sfRenderWindow_drawRectangleShape(context->view->window,
            player->utils->deadrect, 0);
}

void player_render_draw(wolf_context_t *context)
{
    multithread_render(context);
    for (int i = 0; i < context->n_players; i++) {
        player_draw(context, context->players[i]);
    }
}
