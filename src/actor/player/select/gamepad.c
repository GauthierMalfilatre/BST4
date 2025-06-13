/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Selection of player with gamepad
*/
#include "wolf.h"

static int decrease_index(int *index)
{
    (*index)--;
    return 1;
}

static int increase_index(int *dindex)
{
    (*dindex)++;
    return 1;
}

char player_select_gamepad(player_t *player, int *index, int *dindex)
{
    float speedx = sfJoystick_getAxisPosition(player->device - 1, sfJoystickX);
    float speedy = sfJoystick_getAxisPosition(player->device - 1, sfJoystickV);

    if (speedx > 10.f) {
        return increase_index(index);
    }
    if (speedx < -10.f) {
        return decrease_index(index);
    }
    if (speedy < -10.f) {
        return 2 * decrease_index(dindex);
    }
    if (speedy > 10.f) {
        return 2 * increase_index(dindex);
    }
    return 0;
}
