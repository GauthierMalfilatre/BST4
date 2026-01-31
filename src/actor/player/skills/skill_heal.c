/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Skill heal
*/
#include "wolf.h"

int skill_heal(bst_context_t *context, player_t *self)
{
    player_t *ally = (player_t *) 0;

    (void)context;
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = 45000.f;
        add_healing_to_player(self, self->character->maxhp / 2.f / 10.f, 10.f * 1000.f);
        ally = get_nearest_ally(context->players, self, context->n_players);
        if (ally) {
            add_healing_to_player(ally, ally->character->maxhp / 2.f / 10.f, 10.f * 1000.f);
        }
        reinit_bleeding(&self->bleeding);
    }
    return OK;
}

int skill_heal_end(bst_context_t *context, player_t *self, sfBool force)
{
    (void)context;
    if (force || (self->cooldowns.till_competence <= 35000.f &&
        self->cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
    }
    return OK;
}
