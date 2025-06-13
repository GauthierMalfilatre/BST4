/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Skill heal
*/
#include "wolf.h"

static player_t *get_nearest(player_t **players, player_t *player, int i)
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
        if ((((norm <= min_norme) || isnan(min_norme)) && norm <= 500.f) && players[i]->equipe == player->equipe && players[i]->infos.life <= 0.f) {
            min_norme = norm;
            character = players[i];
        }
    }
    return character;
}

int skill_tp(wolf_context_t *context, player_t *self)
{
    player_t *player = 0;

    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = self->character->skill_cooldown;    
        player = get_nearest(context->players, self, context->n_players);
        if (player) {
            player->infos.life = player->character->maxhp / 2.f;
        }        
    }
    return OK;
}

int skill_tp_end(wolf_context_t *context, player_t *self, sfBool force)
{
    (void)context;
    if (force || (self->cooldowns.till_competence <=
        self->character->endskill_cooldown &&
        self->cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
    }
    return OK;
}
