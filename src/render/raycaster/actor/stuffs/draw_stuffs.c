/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Draw players sprite
*/
#include "wolf.h"
#include "../../../render.h"

void draw_stuffs(wolf_context_t *context, player_t *player)
{
    int x_out;
    double depth_out;

    for (stuffs_t *temp = context->cmap->stuffs; temp; temp = temp->next) {
        if (project_stuff_on_screen(player, temp->pos, &x_out, &depth_out) &&
            get_norme(*player->x, *player->y, temp->pos.x, temp->pos.y)
            >= 50) {
            draw_sprite((sfVector2f){x_out, depth_out}, player,
                get_texture_from_type(context->textures, temp->type),
                (sfIntRect){-1, 0, 0, 0});
        }
    }
}
