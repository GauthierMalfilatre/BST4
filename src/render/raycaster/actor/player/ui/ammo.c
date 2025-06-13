/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../../render.h"
#include "scenes.h"

void draw_ammo(player_t *player)
{
    sfColor color = sfWhite;
    int w = (200) * (player->infos.ammo * (1.f / player->character->ammo));

    if (player->infos.ammo < player->character->ammo / 2) {
        color = sfColor_fromRGB(255, 200, 0);
        if (player->infos.ammo < player->character->ammo * 1 / 10) {
            color = sfRed;
        }
    }
    draw_rect(player, (sfVector4i_t){player->param.size.x / 2 - 100,
        player->param.size.y - 60, w, 8}, color, UX_CHN);
}
