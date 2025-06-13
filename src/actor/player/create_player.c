/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Create players.
*/
#include "wolf.h"
#include "math.h"
#include <SDL.h>

static int create_view_param(view_param_t *param, const int i, sfVideoMode v)
{
    *param = (view_param_t) {.size = (sfVector2i) {640, 480}, .offx = (i % 2)
        * ((v.width - 640)), .offy = (i / 2) * (480 + 1080 - 480 * 2),
        .casted_rays = 640, .fov = 60 * M_PI / 180};
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

static void init_random_stuff(player_t *player)
{
    player->voicelines = (voicelines_t){0, 0, 0, 0, 0, 0, 0, 0};
    player->kd = (sfVector2i){0, 0};
    player->cooldowns = (cooldowns_t){0.f, 0.f, 0.f, 0.f};
    player->base_x = 0;
    player->base_y = 0;
    player->x = &player->base_x;
    player->y = &player->base_y;
    player->base_angle = M_PI / 2;
    player->angle = &player->base_angle;
    player->delta_t = 0.f;
    player->hitbox_radius = 20;
    player->time = &player_timer;
    player->equipe = 0;
    player->score = 0;
    reinit_bleeding(&player->bleeding);
    reinit_healing(&player->healing);
    player->is_endskill_used = 0;
    player->is_bleeding_others = 0;
    player->blood = (blood_t *) 0;
    player->killer = (player_t *) 0;
}

static int create_draw_utils(draw_utils_t **draw_utils, view_param_t param)
{
    if (!draw_utils)
        return ERROR;
    *draw_utils = malloc(sizeof(draw_utils_t));
    if (!*draw_utils)
        return ERROR;
    (*draw_utils)->render_texture =
        sfTexture_create(param.size.x, param.size.y);
    (*draw_utils)->render_sprite = sfSprite_create();
    sfSprite_setTexture((*draw_utils)->render_sprite,
        (*draw_utils)->render_texture, 0);
    sfSprite_setPosition((*draw_utils)->render_sprite,
        (sfVector2f) {param.offx, param.offy});
    (*draw_utils)->deadrect = sfRectangleShape_create();
    sfRectangleShape_setSize((*draw_utils)->deadrect, (sfVector2f){640, 480});
    sfRectangleShape_setFillColor((*draw_utils)->deadrect,
        sfColor_fromRGBA(0, 0, 0, 255 / 3));
    (*draw_utils)->self_rect = (sfIntRect){0, 0, 640, 480};
    (*draw_utils)->apparance_rect = (sfIntRect){82, 0, 82, 128};
    return OK;
}

static void init_game_data(player_t *player)
{
    player->infos = (game_meta_t) {.ammo = 100, .atk = PLAYER_BASE_ATK,
        .life = 100, .rdi = IDLING};
}

int set_sound_attenuation(voicelines_t voices, wolf_context_t *context)
{
    unsigned int volume = context->w_setting[W_SOUND];

    sfSound_setVolume(voices.death, volume);
    sfSound_setVolume(voices.heal, volume);
    sfSound_setVolume(voices.midlife, volume);
    sfSound_setVolume(voices.reload, volume);
    sfSound_setVolume(voices.selection, volume);
    sfSound_setVolume(voices.shot, volume);
    sfSound_setVolume(voices.skill, volume);
    sfSound_setVolume(voices.win, volume);
    return OK;
}

int init_player_voicelines(player_t *player, wolf_context_t *context)
{
    player->voicelines.death =
        sfSound_copy(player->character->voicelines.death);
    player->voicelines.heal = sfSound_copy(player->character->voicelines.heal);
    player->voicelines.midlife =
        sfSound_copy(player->character->voicelines.midlife);
    player->voicelines.reload =
        sfSound_copy(player->character->voicelines.reload);
    player->voicelines.selection =
        sfSound_copy(player->character->voicelines.selection);
    player->voicelines.shot = sfSound_copy(player->character->voicelines.shot);
    player->voicelines.skill =
        sfSound_copy(player->character->voicelines.skill);
    player->voicelines.win = sfSound_copy(player->character->voicelines.win);
    if (!player->voicelines.death || !player->voicelines.heal || !player->
        voicelines.midlife || !player->voicelines.reload || !player->
        voicelines.reload || !player->voicelines.selection || !player->
        voicelines.shot || !player->voicelines.skill ||
        !player->voicelines.win)
        return ERROR;
    return set_sound_attenuation(player->voicelines, context);
}

void init_sdl(player_t *player)
{
    int i = player->device - 1;

    player->sdl.gc = 0;
    player->sdl.js = 0;
    player->sdl.h = 0;
    if (i < 0)
        return;
    if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) != 0 ||
        !SDL_IsGameController(i))
        return;
    player->sdl.gc = SDL_GameControllerOpen(i);
    if (!player->sdl.gc)
        return;
    player->sdl.js = SDL_GameControllerGetJoystick(player->sdl.gc);
    player->sdl.h = SDL_HapticOpenFromJoystick(player->sdl.js);
    if (!player->sdl.h || SDL_HapticRumbleInit(player->sdl.h) != 0) {
        if (player->sdl.h)
            SDL_HapticClose(player->sdl.h);
        SDL_GameControllerClose(player->sdl.gc);
        return;
    }
}

int create_player(player_t **player, const int i, sfVideoMode v)
{
    if (!player)
        return ERROR;
    *player = malloc(sizeof(player_t));
    if (!*player)
        return ERROR;
    (*player)->clock = sfClock_create();
    if (create_view_param(&(*player)->param, i, v) == ERROR) {
        return ERROR;
    }
    if (create_buffer(&(*player)->framebuffer, &(*player)->zbuffer,
        (*player)->param) == ERROR)
        return ERROR;
    if (create_draw_utils(&(*player)->utils, (*player)->param) == ERROR)
        return ERROR;
    init_random_stuff(*player);
    init_game_data(*player);
    (*player)->is_visible = sfTrue;
    (*player)->endskill_reserve = 0;
    (*player)->skill_reserve = 0;
    (*player)->messages = (messages_t *) 0;
    return OK;
}
