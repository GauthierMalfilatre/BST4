/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

int skill_dash(wolf_context_t *context, player_t *self)
{
    sfVector2f target_pos;
    sfVector2f base_pos;

    if (self->cooldowns.till_competence <= 0.f) {
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = 5000.f;
        base_pos = (sfVector2f){ *self->x, *self->y };
        target_pos = (sfVector2f){
            base_pos.x - cos(*self->angle) * 3000.0f,
            base_pos.y + sin(*self->angle) * 3000.0f,
        };
        move_player_to(self, base_pos, target_pos, context);
    }
    return OK;
}

int skill_dash_end(wolf_context_t *context, player_t *self, sfBool force)
{
    (void) context;
    (void) force;
    self->is_endskill_used = 1;
    return OK;
}
