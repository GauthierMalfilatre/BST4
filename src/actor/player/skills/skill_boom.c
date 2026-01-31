/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Skill boom! for bsr4.
** Ca t'enlève 50% de tes PV actuels. Tu ne peux pas mourir de ce retrait.
** En échange, pour chaque pv de perdu, tu gagnes 0.33 d'attaque
** Pendant 10 secondes, au bout desquelles tu regagnes 25% de tes pvmax et perds l'attaque supplémentaire.
*/
#include "wolf.h"

int skill_boom(bst_context_t *context, player_t *self)
{
    float ammount = 0.f;

    (void)context;
    if (self->cooldowns.till_competence <= 0.f) {
        self->is_endskill_used = 0;
        sfSound_play(self->voicelines.skill);
        self->cooldowns.till_competence = self->character->skill_cooldown;
        ammount = self->infos.life / 2.f;
        self->infos.life -= ammount;
        self->infos.atk += ammount / 5.f;
    }
    return OK;
}

int skill_boom_end(bst_context_t *context, player_t *self, sfBool force)
{
    (void) context;
    if (force || (self->cooldowns.till_competence <= self->character->endskill_cooldown
        && self->cooldowns.till_competence > 0.f && !self->is_endskill_used)) {
        self->is_endskill_used = 1;
        if (self->infos.life > 0)
            self->infos.life += self->character->maxhp / 4.f;
        if (self->infos.life > self->character->maxhp) {
            self->infos.life = self->character->maxhp;
        }
        self->infos.atk = self->character->atk;
    }
    return OK;
}
