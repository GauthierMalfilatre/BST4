/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Skill heal
*/
#include "wolf.h"

int skill_radiance(bst_context_t *context, player_t *self)
{
    (void)context;
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = self->character->skill_cooldown;
        for (int i = 0; i < context->n_players; i++) {
            if (context->players[i]->equipe != self->equipe || get_norme(
                *context->players[i]->x, *context->players[i]->y, *self->x,
                *self->y) >= 500.f) {
                continue;
            }
            add_buff(&context->players[i]->buff, BUFF_HP, 20.f, MILLI(20.f));
            add_buff(&context->players[i]->buff, BUFF_ATK, 10.f, MILLI(20.f));
            add_buff(&context->players[i]->buff, BUFF_ATKSPD, 50.f, MILLI(20.f));
            add_buff(&context->players[i]->buff, BUFF_SPD, 25.f, MILLI(20.f));
            add_buff(&context->players[i]->buff, BUFF_AMMO, 25.f, MILLI(20.f));
        }
    }
    return OK;
}

int skill_radiance_end(bst_context_t *context, player_t *self, sfBool force)
{
    (void) context;
    if (force || (self->cooldowns.till_competence <= self->character->endskill_cooldown
        && self->cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
        // Code endskill here
    }
    return OK;
}
