/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Movement of player with keypad
*/
#include "wolf.h"

static int change_self_rect(player_t *player, int left)
{
    player->utils->self_rect.left = left;
    return 0;
}

int change_rect(player_t *player)
{
    float atkspd;

    if (player->cooldowns.till_reload > 0)
        return change_self_rect(player, 640 * 6);
    if (!player->infos.ammo)
        return change_self_rect(player, 640 * 5);
    if (player->cooldowns.till_shot > 0) {
        atkspd = (float)player->character->cooldown_till_shot;

        if (player->is_left_hand) {
            if (player->cooldowns.till_shot > atkspd / 2.f)
                return change_self_rect(player, 640 * 3);
            else
                return change_self_rect(player, 640 * 4);
        } else {
            if (player->cooldowns.till_shot > atkspd / 2.f)
                return change_self_rect(player, 640 * 1);
            else
                return change_self_rect(player, 640 * 2);
        }
    }
    return change_self_rect(player, 640 * 0);
}
