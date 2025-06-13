/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

static void resolve_axis(float *speedx, float *speedy, float *speedu)
{
    if (*speedy > 0)
        *speedy /= 2;
    if (fabs(*speedx) < 3.f)
        *speedx = 0;
    if (fabs(*speedy) < 3.f)
        *speedy = 0;
    if (fabs(*speedu) < 3.f)
        *speedu = 0;
}

static void apply_axis(player_t *player, sfVector2f speedxy,
    float speedu, wolf_context_t *context)
{
    float speedx = speedxy.x;
    float speedy = speedxy.y;
    sfVector2f base_pos = {*player->x, *player->y};
    sfVector2f target_pos = base_pos;

    target_pos.x -= -sin(*player->angle) * speedy;
    target_pos.y -= cos(*player->angle) * speedy;
    target_pos.x += -sin(*player->angle + M_PI_2) * speedx;
    target_pos.y += cos(*player->angle + M_PI_2) * speedx;
    move_player_to(player, base_pos, target_pos, context);
    *player->angle += speedu * 0.01f;
}

static void resolve_buttons(player_t *player, int gamenum,
    wolf_context_t *context)
{
    int duck = sfJoystick_getAxisPosition(gamenum, sfJoystickZ);

    if (duck > -50.f) {
        player->infos.rdi = DUCKING;
    }
    if (sfJoystick_isButtonPressed(gamenum, 2) && player->infos.ammo < 100) {
        reload(player);
    }
    if (sfJoystick_isButtonPressed(gamenum, 3)) {
        player->character->skill(context, player);
        rumble_controller(player);
    }
    if (sfJoystick_isButtonPressed(gamenum, 1))
        player->infos.rdi = EMOTING;
    interact_sheep(player, context);
}

static void resolve_rdi(player_t *player, float speedx, float speedy)
{
    if (speedx || speedy) {
        player->infos.gamepad_is_ducking = 0;
        player->infos.rdi = (sqrtf(speedx * speedx + speedy * speedy) < 8.f ?
            WALKING : RUNNING);
    }
    if (player->infos.rdi == RUNNING)
        player->param.fov = DEG_TO_RAD(55);
    else
        player->param.fov = DEG_TO_RAD(60);
}

void player_movement_gamepad(wolf_context_t *context, player_t *player)
{
    int gamenum = player->device - 1;
    float speed = player->delta_t / (3.f * 8.f);
    float speedy = sfJoystick_getAxisPosition(gamenum, sfJoystickY) / 10.f;
    float speedx = sfJoystick_getAxisPosition(gamenum, sfJoystickX) / 10.f;
    float speedu = sfJoystick_getAxisPosition(gamenum, sfJoystickU) / 10.f;

    if (!sfJoystick_isConnected(gamenum))
        return;
    player->infos.rdi = (player->infos.rdi == EMOTING) ? EMOTING : IDLING;
    resolve_axis(&speedx, &speedy, &speedu);
    apply_axis(player, (sfVector2f){speedx * speed, speedy * speed},
        speedu, context);
    resolve_buttons(player, gamenum, context);
    resolve_rdi(player, speedx, speedy);
    if (sfJoystick_getAxisPosition(gamenum, sfJoystickR) > - 50.f)
        shot(context, player);
    change_rect(player);
    return;
}
