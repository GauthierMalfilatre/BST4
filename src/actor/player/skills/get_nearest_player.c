/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

player_t *get_nearest_ally(player_t **players, player_t *player, int i)
{
    float min_norme = NAN;
    player_t *character = 0;
    float norm;
    
    i--;
    for (; i >= 0; i--) {
        if (player == players[i]) {
            continue;
        }
        norm = get_norme(*player->x, *player->y, *players[i]->x, *players[i]->y); 
        if (((norm) <= min_norme || isnan(min_norme)) && norm <= 500.f && players[i]->equipe == player->equipe) {
            min_norme = norm;
            character = players[i];
        }
    }
    return character;
}

player_t *get_nearest_enemy(player_t **players, player_t *player, int i)
{
    float min_norme = NAN;
    player_t *character = 0;
    float norm;

    i--;
    for (; i >= 0; i--) {
        if (player == players[i]) {
            continue;
        }
        norm = get_norme(*player->x, *player->y, *players[i]->x, *players[i]->y); 
        if (((norm) <= min_norme || isnan(min_norme)) && norm <= 500.f && players[i]->equipe != player->equipe) {
            min_norme = norm;
            character = players[i];
        }
    }
    return character;
}
