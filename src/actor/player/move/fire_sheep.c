/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"
#include "sound.h"

void fire_sheep(player_t *player, wolf_context_t *context)
{
    if (context->bs->is_carried != player) {
        return;
    }
    context->bs->firing += player->delta_t;
    if (context->bs->firing >= 4000.f) {
        context->bs->firing = 4000.f;
        context->bs->is_fired = 1;
        drop_blacksheep(context);
        context->bst->timelimit = sfTime_asSeconds(
            sfClock_getElapsedTime(context->bst->clock)) + 45.f;
        player->score += 500;
        play_if_exists(context->w_sound.sounds, "__bs_fired");
        printf("Player %s (%p) has fired the blacksheep\n",
            player->name, player);
    }
}

void eteint_le_noir_mouton(wolf_context_t *context)
{
    context->bs->firing = 0.f;
    context->bs->is_fired = 0;
    context->bs->diffusing = 0;
}

void defire_sheep(player_t *player, wolf_context_t *context)
{
    if (context->bs->diffusing != player || !player->equipe ||
        !context->bs->is_fired) {
        return;
    }
    context->bs->firing -= player->delta_t;
    if (context->bs->firing <= 0.f) {
        eteint_le_noir_mouton(context);
        player->score += 2000;
        made_team_win(context, 1);
        printf("Player %s (%p) has diffusing the blacksheep\n",
            player->name, player);
    }
}
