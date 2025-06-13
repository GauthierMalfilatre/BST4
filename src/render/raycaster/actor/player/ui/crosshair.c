/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../../render.h"
#include "scenes.h"

void draw_cursor(player_t *player)
{
    rdi_t rdi = player->infos.rdi;

    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 10 - 5 * rdi,
        player->param.size.y / 2 - 1, 1 + 10, 1 + 1 * 2}, sfGreen, UX_CHN);
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 1,
        player->param.size.y / 2 - 10 - 5 * rdi, 1 + 1 * 2, 1 + 10},
        sfGreen, UX_CHN);
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 + 5 * rdi,
        player->param.size.y / 2 - 1, 1 + 10, 1 + 1 * 2}, sfGreen, UX_CHN);
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 1,
            player->param.size.y / 2 + 5 * rdi, 1 + 1 * 2, 1 + 10},
            sfGreen, UX_CHN);
}
