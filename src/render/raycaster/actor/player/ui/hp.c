/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../../render.h"
#include "scenes.h"

static void draw_cadre(player_t *player)
{
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100,
        player->param.size.y - 50, 2, 30}, sfWhite, UX_CHN);
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100,
        player->param.size.y - 50, 200, 2}, sfWhite, UX_CHN);
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100,
        player->param.size.y - 22, 200, 2}, sfWhite, UX_CHN);
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 + 100 - 2,
        player->param.size.y - 50, 2, 30}, sfWhite, UX_CHN);
}

static void draw_life_bleeding(player_t *player, float first_step,
    sfColor color)
{
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100 + 4,
        player->param.size.y - 50 + 4, (200 - 8) * (first_step * 1 /
        player->character->maxhp), 30 - 8}, color, UX_CHN);
    if (!player->bleeding.dps)
        return;
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100 + 4 +
        (200 - 8) * (first_step * 1 / player->character->maxhp), player->param.size.y - 50 + 4,
        (200 - 8) * ((player->infos.life - first_step) * 1 / player->
        character->maxhp), 30 - 8}, sfColor_fromRGB(138, 3, 3), UX_CHN);
}

static void draw_life_healing(player_t *player)
{
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100 + 4 +
        (200 - 8) * (player->infos.life * 1 / player->character->maxhp), player->param.size.y -
        50 + 4, (200 - 8) * ((player->healing.target_life -
        player->infos.life) * 1 / player->character->maxhp), 30 - 8}, sfGreen, UX_CHN);
}

static void draw_hps_numbers(player_t *player)
{
    char kronk_buffer[32] = {};

    sprintf(kronk_buffer, "%d", (int)player->infos.life);
    draw_text(player, kronk_buffer, (sfVector4i_t){player->param.size.x / 2 -
        100 + 10, player->param.size.y - 50 + 7, 3, UX_CHN}, sfBlack);
}

void draw_hps(player_t *player)
{
    sfColor color = player->infos.life > player->character->maxhp / 2.f ?
        sfWhite : sfColor_fromRGB(255, 200, 0);
    float first_step = player->bleeding.dps ?
        player->bleeding.target_life : player->infos.life;

    if (player->infos.life < player->character->maxhp * 1 / 10.f)
        color = sfRed;
    draw_cadre(player);
    draw_life_bleeding(player, first_step, color);
    if (player->healing.hps) {
        draw_life_healing(player);
    }
    draw_hps_numbers(player);
}
