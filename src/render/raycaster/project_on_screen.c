/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Draw players sprite
*/
#include "wolf.h"
#include "../render.h"

int project_stuff_on_screen(player_t *player, sfVector2f pos,
    int *screen_x_out, double *depth_out)
{
    double fov = player->param.fov;
    double screen_width = player->param.size.x;
    double player_angle = *player->angle;
    double dx = pos.x - *player->x;
    double dy = pos.y - *player->y;
    double dist = sqrt(dx * dx + dy * dy);
    double angle_to_target = atan2(-dx, dy);
    double angle_diff = angle_to_target - player_angle;

    while (angle_diff < -1 * M_PI)
        angle_diff += 2 * M_PI;
    while (angle_diff > M_PI)
        angle_diff -= 2 * M_PI;
    if (fabs(angle_diff) > fov / 2.0)
        return 0;
    *screen_x_out = (int)((angle_diff / (fov / 2.0)) * (screen_width / 2.0)
                    + (screen_width / 2.0));
    *depth_out = dist;
    return 1;
}
