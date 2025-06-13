/*
** EPITECH PROJECT, 2024
** sldier_to_percentage
** File description:
** slider value to percentage
*/

#include "setting_sliders.h"

float resolution_to_percentage(int value)
{
    int min = resolutions[0];
    int max = resolutions[resolution_count - 1];

    if (value < min)
        value = min;
    if (value > max)
        value = max;
    return ((float)(value - min) / (float)(max - min)) * 100.0f;
}

float framerate_to_percentage(int value)
{
    if (value < MIN_FPS)
        value = MIN_FPS;
    if (value > MAX_FPS)
        value = MAX_FPS;
    return ((float)(value - MIN_FPS) / (float)(MAX_FPS - MIN_FPS)) * 100.0f;
}

float sound_to_percentage(int value)
{
    if (value < MIN_SOUND)
        value = MIN_SOUND;
    if (value > MAX_SOUND)
        value = MAX_SOUND;
    return ((float)(value - MIN_SOUND) /
        (float)(MAX_SOUND - MIN_SOUND)) * 100.0f;
}
