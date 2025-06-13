/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

static void project_on_wall(sfVector2f *move,
    sfVector2f wall_a, sfVector2f wall_b)
{
    sfVector2f wall_dir;
    float wall_len_sq;
    float dot;

    wall_dir.x = wall_b.x - wall_a.x;
    wall_dir.y = wall_b.y - wall_a.y;
    wall_len_sq = wall_dir.x * wall_dir.x + wall_dir.y * wall_dir.y;
    if (wall_len_sq == 0)
        return;
    dot = (move->x * wall_dir.x + move->y * wall_dir.y) / wall_len_sq;
    move->x = wall_dir.x * dot;
    move->y = wall_dir.y * dot;
}

static void make_offsets(sfVector2f out[5])
{
    out[0] = (sfVector2f){0, 0};
    out[1] = (sfVector2f){PLAYER_RADIUS, 0};
    out[2] = (sfVector2f){-1 * PLAYER_RADIUS, 0};
    out[3] = (sfVector2f){0, PLAYER_RADIUS};
    out[4] = (sfVector2f){0, -PLAYER_RADIUS};
}

static int detect_collision(wolf_context_t *context,
    sfVector2f from, sfVector2f to)
{
    sfVector2f intersection = {0.0 / 0.0, 0.0 / 0.0};

    for (int i = 0; i < context->cmap->n_wall; i++) {
        if (!context->cmap->walls[i].a.x && !context->cmap->walls[i].b.x)
            break;
        if (get_intersect(&context->cmap->walls[i], from, to,
            &intersection) == OK)
            return i;
    }
    return -1;
}

static int try_project_move(sfVector2f *move,
    sfVector2f *pos, sfVector2f *target, wolf_context_t *context)
{
    sfVector2f offsets[5];
    sfVector2f offset_pos;
    sfVector2f offset_target;
    int hit;

    make_offsets(offsets);
    for (int d = 0; d < 5; d++) {
        offset_pos.x = pos->x + offsets[d].x;
        offset_pos.y = pos->y + offsets[d].y;
        offset_target.x = target->x + offsets[d].x;
        offset_target.y = target->y + offsets[d].y;
        hit = detect_collision(context, offset_pos, offset_target);
        if (hit != -1) {
            project_on_wall(move, context->cmap->walls[hit].a,
                context->cmap->walls[hit].b);
            return 1;
        }
    }
    return 0;
}

static int check_after_projection(sfVector2f *pos,
    sfVector2f *projected, wolf_context_t *ctx)
{
    sfVector2f offsets[5];
    sfVector2f offset_pos;
    sfVector2f offset_target;

    make_offsets(offsets);
    for (int d = 0; d < 5; d++) {
        offset_pos.x = pos->x + offsets[d].x;
        offset_pos.y = pos->y + offsets[d].y;
        offset_target.x = projected->x + offsets[d].x;
        offset_target.y = projected->y + offsets[d].y;
        if (detect_collision(ctx, offset_pos, offset_target) != -1)
            return 1;
    }
    return 0;
}

int handle_slide_collision_radius(sfVector2f *pos,
    sfVector2f target, wolf_context_t *ctx)
{
    sfVector2f move;
    sfVector2f projected;
    float factor = 1.0f;

    move.x = target.x - pos->x;
    move.y = target.y - pos->y;
    try_project_move(&move, pos, &target, ctx);
    while (factor > 0.01f) {
        projected.x = pos->x + move.x * factor;
        projected.y = pos->y + move.y * factor;
        if (!check_after_projection(pos, &projected, ctx)) {
            pos->x = projected.x;
            pos->y = projected.y;
            return OK;
        }
        factor *= 0.5f;
    }
    return ERROR;
}
