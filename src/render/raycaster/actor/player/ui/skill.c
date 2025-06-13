/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../../render.h"
#include "scenes.h"

void draw_skill(player_t *player)
{
    char buffer[32];
    sfColor color = player->cooldowns.till_competence <= 0.f ?
        sfColor_fromRGBA(255, 255, 255, 0) : sfColor_fromRGBA(80, 80, 80, 140);

    draw_circle(player, (sfVector4i_t){560, 400, 50, 0}, UX_CHN, color);
    if (player->cooldowns.till_competence <= 0.f) {
        draw_text(player, player->device ? "y" : "e",
            (sfVector4i_t){545, 380, 10, UX_CHN}, sfRed);
    } else {
        sprintf(buffer, "%d", (int)(player->cooldowns.till_competence / 1000.f));
        draw_text(player, buffer,
            (sfVector4i_t){540, 385, 6, UX_CHN}, sfRed);
    }
}
