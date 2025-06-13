/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Movement of player with keypad
*/
#include "wolf.h"
#include "scenes.h"

static void resolve_alt(wolf_context_t *context, player_t *player)
{
    sfVector2i mouse_pos =
        sfMouse_getPositionRenderWindow(context->view->window);
    sfVector2u win_size = sfRenderWindow_getSize(context->view->window);
    sfVector2i center = { (int)win_size.x / 2, (int)win_size.y / 2 };
    int delta_x = (mouse_pos.x - center.x) *
        (float)context->w_setting[W_SENSIBILITE] / 100;
    float sensitivity = 0.005f;

    if (!context->is_alt) {
        *player->angle += delta_x * sensitivity * player->delta_t / 15;
        if (*player->angle < 0)
            *player->angle += 2 * M_PI;
        if (*player->angle >= 2 * M_PI)
            *player->angle -= 2 * M_PI;
        sfMouse_setPositionRenderWindow(center, context->view->window);
    }
}

static void resolve_keyboard(sfVector2f *target_pos, player_t *player,
    float speed, int *move)
{
    if (sfKeyboard_isKeyPressed(sfKeyW)) {
        target_pos->x += -sin(*player->angle) * speed;
        target_pos->y += cos(*player->angle) * speed;
        (*move)++;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        target_pos->x -= -sin(*player->angle) * speed / 2;
        target_pos->y -= cos(*player->angle) * speed / 2;
        (*move)++;
    }
    if (sfKeyboard_isKeyPressed(sfKeyA)) {
        target_pos->x -= -sin(*player->angle + M_PI_2) * speed;
        target_pos->y -= cos(*player->angle + M_PI_2) * speed;
        (*move)++;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        target_pos->x -= -sin(*player->angle - M_PI_2) * speed;
        target_pos->y -= cos(*player->angle - M_PI_2) * speed;
        (*move)++;
    }
}

static void resolve_keyboard2(player_t *player, wolf_context_t *context)
{
    if (sfKeyboard_isKeyPressed(sfKeyH)) {
        player->infos.rdi = EMOTING;
    }
    if (sfKeyboard_isKeyPressed(sfKeyR) && player->infos.ammo < 100) {
        reload(player);
    }
    if (sfKeyboard_isKeyPressed(sfKeyE)) {
        player->character->skill(context, player);
    }
    if (sfKeyboard_isKeyPressed(sfKeyO)) {
        made_team_win(context, 1);
    }
    interact_sheep(player, context);
}

static void resolve_rdi(player_t *player)
{
    if (player->infos.rdi == RUNNING)
        player->param.fov = DEG_TO_RAD(55);
    else
        player->param.fov = DEG_TO_RAD(60);
}

void player_movement_keyboard(wolf_context_t *context, player_t *player)
{
    int move = 0;
    float speed = player->delta_t / 3.f;
    sfVector2f base_pos = {*player->x, *player->y};
    sfVector2f target_pos = {*player->x, *player->y};
    int isls = sfKeyboard_isKeyPressed(sfKeyLShift);

    player->infos.rdi = player->infos.rdi == EMOTING ? EMOTING : IDLING;
    if (sfKeyboard_isKeyPressed(sfKeyLControl))
        player->infos.rdi = DUCKING;
    resolve_alt(context, player);
    resolve_keyboard(&target_pos, player, speed * (isls ? 1.3f : 1.f), &move);
    if (move)
        player->infos.rdi = (isls) ? RUNNING : WALKING;
    resolve_rdi(player);
    move_player_to(player, base_pos, target_pos, context);
    if (sfMouse_isButtonPressed(sfMouseLeft) && !context->is_alt) {
        shot(context, player);
    }
    resolve_keyboard2(player, context);
    change_rect(player);
}
