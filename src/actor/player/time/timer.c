/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy players.
*/
#include "wolf.h"

void player_timer(player_t *player, wolf_context_t *context)
{
    player->delta_t = sfTime_asMilliseconds(sfClock_restart(player->clock));
    if (player->cooldowns.till_competence > 0.f) {
        player->cooldowns.till_competence -= player->delta_t;
    }
    if (player->cooldowns.till_reload > 0.f) {
        player->cooldowns.till_reload -= player->delta_t;
    }
    if (player->cooldowns.till_shot > 0.f) {
        player->cooldowns.till_shot -= player->delta_t;
    }
    if (player->cooldowns.till_respawn > 0.f) {
        player->cooldowns.till_respawn -= player->delta_t;
        if (player->cooldowns.till_respawn <= 0.f) {
            spawn(player, context);
        }
    }
    update_blood(&player->blood, player);
    update_messages(player);
    return;
}
