/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Create players.
*/
#include "wolf.h"

static int create_view_param(view_param_t *param, const int i)
{
    *param = (view_param_t) {.size = (sfVector2i) {640, 480}, .offx = i % 2,
        .offy = i / 2, .casted_rays = 640, .fov = 60};
    return OK;
}

static int create_buffer(sfUint8 **framebuffer, double **zbuffer,
    view_param_t view)
{
    if (!framebuffer || !zbuffer) {
        return ERROR;
    }
    *framebuffer = malloc(sizeof(sfUint8) * view.size.x * view.size.y * 4);
    if (!*framebuffer) {
        return ERROR;
    }
    *zbuffer = malloc(sizeof(double) * view.size.x * view.size.y);
    if (!*zbuffer) {
        free(*framebuffer);
        return ERROR;
    }
    for (int i = 0; i < view.size.x * view.size.y; i++) {
        (*zbuffer)[i] = -1.f;
    }
    return OK;
}

static int create_player_deprecated(player_t **player, const int i)
{
    if (!player)
        return ERROR;
    *player = malloc(sizeof(player_t));
    if (!*player)
        return ERROR;
    (*player)->x = 0;
    (*player)->y = 0;
    (*player)->clock = sfClock_create();
    if (create_view_param(&(*player)->param, i) == ERROR) {
        return ERROR;
    }
    if (create_buffer(&(*player)->framebuffer, &(*player)->zbuffer,
        (*player)->param) == ERROR)
        return ERROR;
    *(*player)->angle = (M_PI / 2);
    (*player)->delta_t = 0;
    (*player)->move = 0;
    (*player)->time = 0;
    return OK;
}

int create_players(player_t ***players, const int n_players)
{
    if (!players) {
        return ERROR;
    }
    (*players) = malloc(sizeof(player_t *) * n_players);
    if (!(*players)) {
        return ERROR;
    }
    for (int i = 0; i < n_players; i++) {
        if (create_player_deprecated(&(*players)[i], i) == ERROR) {
            return ERROR;
        }
    }
    return OK;
}
