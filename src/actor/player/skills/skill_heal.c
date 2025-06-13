/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Skill heal
*/
#include "wolf.h"

int skill_heal(wolf_context_t *context, player_t *self)
{
    (void)context;
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = 45000.f;
        add_healing_to_player(self, 2.5f, 10.f * 1000.f);
        reinit_bleeding(&self->bleeding);
    }
    return OK;
}

int skill_heal_end(wolf_context_t *context, player_t *self, sfBool force)
{
    (void)context;
    if (force || (self->cooldowns.till_competence <= 35000.f &&
        self->cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
    }
    return OK;
}
