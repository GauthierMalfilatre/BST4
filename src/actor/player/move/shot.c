/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Movement of player with keypad
*/
#include "wolf.h"
#include "sound.h"

void shot(wolf_context_t *context, player_t *player)
{
    if (player->cooldowns.till_shot > 0 || player->cooldowns.till_reload > 0) {
        return;
    }
    if (player->infos.ammo > 0) {
        player->is_visible = sfTrue;
        sfSound_play(player->voicelines.shot);
        add_bullet(&context->cmap->bullets, player);
        player->is_left_hand = !player->is_left_hand;
        player->infos.ammo--;
        player->cooldowns.till_shot = player->infos.atkspd;
    }
}

void reload(player_t *player)
{
    play_force(player->voicelines.reload);
    player->infos.ammo = player->character->ammo;
    player->cooldowns.till_reload = 3000.f;
}
