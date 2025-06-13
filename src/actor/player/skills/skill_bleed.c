/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

int skill_bleeding(wolf_context_t *context, player_t *self)
{
    (void)context;
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = 30000.f;
        self->is_bleeding_others = 1;
    }
    return OK;
}

int skill_bleeding_end(wolf_context_t *context, player_t *self, sfBool force)
{
    (void) context;
    if (force || (self->cooldowns.till_competence <= 20000.f
        && self->cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
        self->is_bleeding_others = 0;
    }
    return OK;
}
