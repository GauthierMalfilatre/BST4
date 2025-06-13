/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Skill heal
*/
#include "wolf.h"

int skill_invisible(wolf_context_t *context, player_t *self)
{
    (void)context;
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = 45000.f;
        self->is_visible = sfFalse;
    }
    return OK;
}

int skill_invisible_end(wolf_context_t *context, player_t *self, sfBool force)
{
    (void)context;
    if (force || (self->cooldowns.till_competence <= 30000.f &&
        self->cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
        self->is_visible = sfTrue;
    }
    return OK;
}
