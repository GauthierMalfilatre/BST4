/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy players.
*/
#include "wolf.h"

static void delete_voicelines(voicelines_t voicelines)
{
    if (voicelines.death)
        sfSound_destroy(voicelines.death);
    if (voicelines.heal)
        sfSound_destroy(voicelines.heal);
    if (voicelines.midlife)
        sfSound_destroy(voicelines.midlife);
    if (voicelines.reload)
        sfSound_destroy(voicelines.reload);
    if (voicelines.selection)
        sfSound_destroy(voicelines.selection);
    if (voicelines.shot)
        sfSound_destroy(voicelines.shot);
    if (voicelines.skill)
        sfSound_destroy(voicelines.skill);
    if (voicelines.win)
        sfSound_destroy(voicelines.win);
}

static void destroy_player(player_t *player)
{
    delete_voicelines(player->voicelines);
    destroy_blood_list(player->blood);
    sfClock_destroy(player->clock);
    sfTexture_destroy(player->utils->render_texture);
    sfSprite_destroy(player->utils->render_sprite);
    sfRectangleShape_destroy(player->utils->deadrect);
    if (player->sdl.h)
        SDL_HapticClose(player->sdl.h);
    if (player->sdl.gc)
        SDL_GameControllerClose(player->sdl.gc);
    free(player->framebuffer);
    free(player->zbuffer);
    free(player->name);
    free(player);
    return;
}

int destroy_players(player_t **players, const int n_players)
{
    if (!players) {
        return ERROR;
    }
    for (int i = 0; i < n_players && players[i]; i++) {
        destroy_player(players[i]);
    }
    free(players);
    return OK;
}
