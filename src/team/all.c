/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Move gestion for bst scene.
*/
#include "wolf.h"
#include "scenes.h"
#include "sound.h"

void give_point_to_team(wolf_context_t *context, const int np)
{
    for (int i = 0; i < context->n_players; i++) {
        context->players[i]->score += np;
    }
}

void made_team_win(wolf_context_t *context, int team)
{
    context->team_winner = team;
    if (team) {
        context->wins.y++;
    } else {
        context->wins.x++;
    }
    for (int i = 0; i < context->n_players; i++) {
        if (context->players[i]->equipe == team) {
            play_force(context->players[i]->character->voicelines.win);
        }
    }
    change_scene(INTERLUDE_SCENE, context);
}
