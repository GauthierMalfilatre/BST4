/*
** EPITECH PROJECT, 2025
** RAYv4
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

static sfBool is_in_point(player_t *player, bsp_t *bsps)
{
    for (bsp_t *temp = bsps; temp; temp = temp->next) {
        if (*player->x > temp->a.x && *player->y > temp->a.y &&
            *player->x < temp->b.x && *player->y < temp->b.y) {
            return sfTrue;
        }
    }
    return sfFalse;
}

static int check_rdi(player_t *player)
{
    if (player->infos.rdi == WALKING || player->infos.rdi == RUNNING) {
        return ERROR;
    }
    return OK;
}

static sfBool select_condition(player_t *player)
{
    if (player->device == 0) {
        return sfKeyboard_isKeyPressed(sfKeyNum4) &&
            !sfMouse_isButtonPressed(sfMouseLeft);
    } else if (player->device >= 1) {
        return sfJoystick_isButtonPressed(player->device - 1, 0) &&
            sfJoystick_getAxisPosition(player->device - 1, sfJoystickR) < 50.f;
    }
    return sfFalse;
}

static void switch_fire(player_t *player, wolf_context_t *context)
{
    if (context->bs->is_fired || !is_in_point(player, context->cmap->bsp)) {
        return;
    }
    if (select_condition(player) && check_rdi(player) == OK) {
        fire_sheep(player, context);
    } else {
        context->bs->firing = 0.f;
    }
}

static void switch_defuse(player_t *player, wolf_context_t *context)
{
    if (context->bs->is_fired == 0) {
        return;
    }
    if (context->bs->diffusing && context->bs->diffusing != player) {
        return;
    }
    if (!context->bs->diffusing) {
        context->bs->diffusing = player;
    }
    if (select_condition(player) && check_rdi(player) == OK) {
        if (get_norme(*player->x, *player->y, context->bs->pos.x,
            context->bs->pos.y) <= 100.f) {
            defire_sheep(player, context);
        }
    } else {
        context->bs->firing = 4000.f;
        context->bs->diffusing = 0;
    }
}

void interact_sheep(player_t *player, wolf_context_t *context)
{
    if (context->mode != BS_GO) {
        return;
    }
    if (player->equipe == 0 && context->bs->is_carried == player) {
        switch_fire(player, context);
    }
    if (player->equipe == 1) {
        switch_defuse(player, context);
    }
}
