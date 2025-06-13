/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Movement of player with keypad
*/
#include "wolf.h"

void move_player_to(player_t *player, sfVector2f base_pos,
    sfVector2f target_pos, wolf_context_t *context)
{
    if (handle_slide_collision_radius(&base_pos, target_pos, context)
        == OK) {
        player->base_x = base_pos.x;
        player->base_y = base_pos.y;
    }
}
