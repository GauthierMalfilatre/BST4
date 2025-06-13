/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Skill add wall
*/
#include "wolf.h"

static void add_the_wall(wolf_context_t *context, player_t *self)
{
    float length = 200;

    if (context->cmap)
    context->cmap->n_wall++;
    context->cmap->walls = realloc(context->cmap->walls, sizeof(wall_t) *
        context->cmap->n_wall);
    context->cmap->walls[context->cmap->n_wall - 1] = (wall_t){
        .a = (sfVector2f){
            *self->x + sin(*self->angle) * -50.f
            - cos(*self->angle) * (length / 2.f),
            *self->y - cos(*self->angle) * -50.f
            - sin(*self->angle) * (length / 2.f)},
        .b = (sfVector2f){
            *self->x + sin(*self->angle) * -50.f
            + cos(*self->angle) * (length / 2.f),
            *self->y - cos(*self->angle) * -50.f
            + sin(*self->angle) * (length / 2.f)},
        .type = 653, .is_breakable = 50, .builder = self};
}

int skill_wall(wolf_context_t *context, player_t *self)
{
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = 60000.f;
        add_the_wall(context, self);
    }
    return OK;
}

static void remove_destructible_walls(wolf_context_t *context, player_t *self)
{
    for (int i = 0; i < context->cmap->n_wall; i++) {
        if (context->cmap->walls[i].is_breakable != 0.f &&
            context->cmap->walls[i].builder == self) {
            remove_wall_at_index(&context->cmap->walls,
                &context->cmap->n_wall, i);
            i--;
        }
    }
}

int skill_wall_end(wolf_context_t *context, player_t *self, sfBool force)
{
    if (force || (self->cooldowns.till_competence <= 30000.f && self->
        cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
        remove_destructible_walls(context, self);
    }
    return OK;
}
