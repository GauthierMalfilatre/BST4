/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

int skill_atk(wolf_context_t *context, player_t *self)
{
    (void)context;
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = 30000.f;
        self->infos.atk = self->character->atk * 2;
    }
    return OK;
}

int skill_atk_end(wolf_context_t *context, player_t *self, sfBool force)
{
    (void) context;
    if (force || (self->cooldowns.till_competence <= 10000.f
        && self->cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
        self->infos.atk = self->character->atk;
    }
    return OK;
}
