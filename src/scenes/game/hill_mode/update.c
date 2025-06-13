/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Move gestion for hill scene.
*/
#include "wolf.h"
#include "scenes.h"

static void sort_list(player_t **players, const int n)
{
    int i = 0;
    player_t *temp;

    while (i < n - 1) {
        if (players[i]->score < players[i + 1]->score) {
            temp = players[i];
            players[i] = players[i + 1];
            players[i + 1] = temp;
            i = 0;
            continue;
        }
        i++;
    }
}

static void check_endgame(wolf_context_t *context)
{
    player_t **player;

    if (!context->hill) {
        return;
    }
    if (sfTime_asSeconds(sfClock_getElapsedTime(context->hill->clock)) >
        context->hill->timelimit) {
        player = malloc(sizeof(player_t *) * context->n_players);
        memcpy(player, context->players,
            sizeof(player_t *) * context->n_players);
        sort_list(player, context->n_players);
        made_team_win(context, player[0]->equipe);
    }
}

void endskill_h(wolf_context_t *context, player_t *player)
{
    if (!player->character || !player->character->endskill) {
        return;
    }
    player->character->endskill(context, player, sfFalse);
}

void update_player_h(wolf_context_t *context, player_t *player)
{
    player->time(player, context);
    if (player->device != -1 && player->infos.life > 0.f) {
        player_resolve_bleeding(player, context);
        player->move(context, player);
        endskill_h(context, player);
    }
}

void hill_update(wolf_context_t *context)
{
    if (!context || !context->hill ||
        context->current_scene != GAME_HILL_SCENE)
        return;
    udpdate_bullets(context);
    for (int i = 0; i < context->n_players; i++) {
        update_player_h(context, context->players[i]);
    }
    check_endgame(context);
}
