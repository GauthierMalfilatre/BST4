/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Skill heal
*/
#include "wolf.h"

int heal_player(player_t *self, const float ammount)
{
    self->infos.life += ammount;
    if (self->infos.life > self->character->maxhp) {
        self->infos.life = self->character->maxhp;
    }
    reinit_bleeding(&self->bleeding);
    printf("Player %s (%p) has recovered %.1f hp.\n", self->name,
        self, ammount);
    return OK;
}
