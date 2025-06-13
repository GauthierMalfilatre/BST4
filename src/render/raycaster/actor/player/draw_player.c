/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Draw players sprite
*/
#include "wolf.h"
#include "../../../render.h"
#include "../../../../scenes/selection/selection.h"

/*
static int is_point_in_line(sfVector2f a, sfVector2f b, sfVector2f c)
{
    float x = c.x;
    float y = c.y;
    float x1 = a.x;
    float y1 = a.y;
    float x2 = b.x;
    float y2 = b.y;
    float AB = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    float AP = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
    float PB = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));

    if (AB == AP + PB)
        return 1;
    return 0;
}
*/
static int project_player_on_screen(player_t *player, player_t *target,
    int *screen_x_out, double *depth_out)
{
    double fov = player->param.fov;
    double screen_width = player->param.size.x;
    double player_angle = *player->angle;
    double dx = *target->x - *player->x;
    double dy = *target->y - *player->y;
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

static float normalize_angle(float angle)
{
    while (angle > M_PI)
        angle -= 2 * M_PI;
    while (angle < -1 * M_PI)
        angle += 2 * M_PI;
    return angle;
}

int is_de_dos(const player_t *src, const player_t *dst)
{
    float dx = cosf(*dst->angle);
    float dy = sinf(*dst->angle);
    float sx = cosf(*src->angle);
    float sy = sinf(*src->angle);
    float angle = normalize_angle(atan2f(dy, dx) - atan2f(sy, sx));

    if (dst->infos.life <= 0.f)
        return 5;
    if (dst->infos.rdi == EMOTING)
        return 4;
    if (fabsf(angle) < M_PI / 4)
        return 2;
    else if (angle >= M_PI / 4 && angle <= 3 * M_PI / 4)
        return 3;
    if (fabsf(angle) > 3 * M_PI / 4)
        return 0;
    else
        return 1;
}

static void draw_name(player_t *player, player_t *target, const int x_out,
    const double depth)
{
    const int screen_w = player->param.size.x;
    const int screen_h = player->param.size.y;
    const int sprite_height = (screen_h * 100) / (depth + 0.0001);
    const int y_start = screen_h / 2 - sprite_height / 2;
    int text_y = y_start - 12;

    if (target->infos.life <= 0.f || player->zbuffer[(screen_h / 2) *
        screen_w + x_out] < depth)
        return;
    draw_rect(player, (sfVector4i_t){x_out - (int)strlen(target->name) / 2 *
        2 * 4 - 2, text_y - 2, strlen(target->name) * 2 * 5 + 4, 5 * 2 + 4},
        team_colors[target->equipe], depth);
    draw_text(player, target->name, (sfVector4i_t)
        {x_out - (int)(strlen(target->name) / 2 * 2 * 4), text_y, 2, depth},
        sfWhite);
}

void draw_mob(wolf_context_t *data, player_t *player)
{
    int screen_x;
    double depth;
    player_t *target;
    sfIntRect rect = {0, 0, 82, 128};

    for (int j = 0; j < data->n_players; j++) {
        target = data->players[j];
        if (player == target || !target->character->apparance)
            continue;
        if (target->is_visible
            && project_player_on_screen(player, target, &screen_x, &depth)) {
            rect.left = is_de_dos(player, target) * 82;
            draw_name(player, target, screen_x, depth);
            draw_sprite_cropped((sfVector2f){screen_x, depth}, player,
                target->character->apparance, rect);
            render_blood(&target->blood, player);
        }
    }
}
