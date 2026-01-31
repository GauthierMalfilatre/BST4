/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Render file for player
*/
#include "wolf.h"
#include "../../../../render.h"
#include "scenes.h"

static void draw_one_ally(bst_context_t *context, player_t *self,
    player_t *target, int n)
{
    char buffer[256];

    (void)context;
    sprintf(buffer, "%s %dm", target->name, (int)get_norme(*target->x, *target->y, *self->x, *self->y) / 100);
    draw_text(self, buffer, (sfVector4i_t){10, 100 + n * 50, 2, UX_CHN}, target->infos.life > 0 ? sfWhite : sfColor_fromRGB(100, 100, 100));
    draw_rect(self, (sfVector4i_t){10, 120 + n * 50, (target->infos.life / (target->infos.maxhp)) * 75, 5},
        target->infos.life < target->infos.maxhp / 10.f ? sfRed : target->infos.life > target->infos.maxhp / 2.f ? sfWhite : sfColor_fromRGB(255, 200, 0), UX_CHN);
    draw_rect(self, (sfVector4i_t){10, 130 + n * 50, (target->infos.ammo / (target->infos.max_ammo)) * 75, 2},
        target->infos.ammo < target->infos.max_ammo / 10.f ? sfRed : target->infos.ammo > target->infos.max_ammo / 2.f ? sfWhite : sfColor_fromRGB(255, 200, 0), UX_CHN);

}

void draw_allies(bst_context_t *context, player_t *self)
{
    int n = 0;

    for (int i = 0; i < context->n_players; i++) {
        if (context->players[i] == self || context->players[i]->equipe != self->equipe) {
            continue;
        }
        draw_one_ally(context, self, context->players[i], n);
        n++;
    }
}
