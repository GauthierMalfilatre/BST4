/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Update buffs
*/
#include "wolf.h"

// Buffs are in percentages.

void apply_buff(player_t *player, buff_t *buff)
{
    if (!player || !buff || buff->duration <= 0.f) {
        return;
    }
    switch (buff->type) {
    case BUFF_HP:
        if (buff->is_first_time == 1) {
            buff->is_first_time = 0;
            player->infos.life *= (1.f + buff->value / 100.f);
        }
        player->infos.maxhp *= (1.f + buff->value / 100);
        break;
    case BUFF_ATK:
        player->infos.atk *= (1.f + buff->value / 100);
        break;
    case BUFF_AMMO:
        if (buff->is_first_time == 1) {
            buff->is_first_time = 0;
            player->infos.ammo *= (1.f + buff->value / 100);
        }
        player->infos.max_ammo *= (1.f + buff->value / 100);
        break;
    case BUFF_ATKSPD:
        player->infos.atkspd /= (1.f + buff->value / 100);
        break;
    case BUFF_SPD:
        player->infos.spd *= (1.f + buff->value / 100);
    default:
        break;
    }
}

void desapply_buff(player_t *player)
{
    (void) player;
    return; // ??
}
