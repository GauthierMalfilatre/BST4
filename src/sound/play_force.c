/*
** EPITECH PROJECT, 2024
** music
** File description:
** all musiic fonction
*/
#include "wolf.h"

void play_force(sfSound *sound)
{
    if (!sound) {
        return;
    }
    if (sfSound_getStatus(sound) != sfPlaying) {
        sfSound_play(sound);
    }
    return;
}
