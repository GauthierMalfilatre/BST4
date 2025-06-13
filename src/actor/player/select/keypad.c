/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Selection of player with keypad
*/
#include "wolf.h"

char player_select_keyboard(player_t *player, int *index, int *dindex)
{
    (void)player;
    if (sfKeyboard_isKeyPressed(sfKeyD) ||
        sfKeyboard_isKeyPressed(sfKeyRight)) {
        (*index)++;
        return 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyA) || sfKeyboard_isKeyPressed(71)) {
        (*index)--;
        return 1;
    }
    if (sfKeyboard_isKeyPressed(sfKeyW) || sfKeyboard_isKeyPressed(sfKeyUp)) {
        (*dindex)--;
        return 2;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(74)) {
        (*dindex)++;
        return 2;
    }
    return 0;
}
