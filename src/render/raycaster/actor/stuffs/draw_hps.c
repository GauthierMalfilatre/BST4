/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Draw players sprite
*/
#include "wolf.h"
#include "../../../render.h"
#include "sound.h"

static void update(wolf_context_t *context, player_t *player, heals_t *temp)
{
    sfClock *clock = context->mode == BS_GO ? context->bst->clock :
        context->hill->clock;

    if (!temp->is_taken &&
        get_norme(*player->x, *player->y, temp->pos.x, temp->pos.y) <= 20.f) {
        add_healing_to_player(player, (float)player->character->maxhp
            / 20.f, 10000.f);
        play_force(player->character->voicelines.heal);
        temp->is_taken = sfTime_asSeconds(sfClock_getElapsedTime(clock));
    }
    if (sfTime_asSeconds(sfClock_getElapsedTime(clock)) -
        temp->is_taken >= 30.f) {
        temp->is_taken = 0.f;
    }
}

void draw_heals(wolf_context_t *context, player_t *player)
{
    int x_out;
    double depth_out;

    for (heals_t *temp = context->cmap->heals; temp; temp = temp->next) {
        update(context, player, temp);
        if (temp->is_taken != 0.f)
            continue;
        if (project_stuff_on_screen(player, temp->pos, &x_out, &depth_out)) {
            draw_sprite((sfVector2f){x_out, depth_out}, player,
                get_texture(context->textures, "__heal"),
                (sfIntRect){-1, 0, 0, 0});
        }
    }
}
