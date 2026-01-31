/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Update buffs
*/
#include "wolf.h"

void update_buff(bst_context_t *context, player_t *player)
{
    buff_t *previous = (buff_t *) 0;

    if (!context || !player) {
        return;
    }
    player->infos.maxhp = player->character->maxhp;
    player->infos.atk = player->character->atk;
    player->infos.atkspd = player->character->cooldown_till_shot;
    player->infos.spd = 1.f;
    player->infos.max_ammo = player->character->ammo;
    for (buff_t *buff = player->buff; buff;) {
        buff->duration -= player->delta_t;
        if (buff->duration <= 0.f) {
            previous = buff;
            buff = buff->next;
            desapply_buff(player, previous);
            remove_buff(&player->buff, previous);
            continue;
        }
        apply_buff(player, buff);
        buff = buff->next;
    }
    player->infos.life = MIN(player->infos.life, player->infos.maxhp);
    player->infos.ammo = MIN(player->infos.ammo, player->infos.max_ammo);
}
