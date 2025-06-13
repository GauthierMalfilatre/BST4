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

    for (; i > 0; i--) {
        if (player == players[i]) {
            continue;
        }
        norm = get_norme(*player->x, *player->y, *players[i]->x, *players[i]->y); 
        if (((norm) <= min_norme || isnan(min_norme)) && norm <= 500.f) {
            min_norme = norm;
            character = players[i];
        }
    }
    return character;
}

int skill_steal(wolf_context_t *context, player_t *self)
{
    player_t *character;

    (void)context;
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = 1000.f;
        character = get_nearest(context->players, self, context->n_players - 1);
        if (!character) {
            return ERROR;
        }
        printf("Stealit !\n");
        self->endskill_reserve = character->character->endskill;
        self->cooldowns.till_competence = 0.f;
        character->character->skill(context, self);
    }
    return OK;
}

int skill_steal_end(wolf_context_t *context, player_t *self, sfBool force)
{
    (void)context;
    if (force || !self->is_endskill_used) {
        if (self->endskill_reserve)
            self->endskill_reserve(context, self, force);
    }
    return OK;
}
