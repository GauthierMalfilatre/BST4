/*
** EPITECH PROJECT, 2024
** sound
** File description:
** all sound fonction
*/

#include "wolf.h"

void play_sound(sfSound *sound)
{
    if (!sound)
        return;
    sfSound_play(sound);
}

void create_sound(wolf_context_t *context)
{
    sound_t sound = {0};

    sound.buffer_click =
        sfSoundBuffer_createFromFile("./assets/menu_assets/click.wav");
    if (!sound.buffer_click) {
        fprintf(stderr, "Failed to load sound\n");
        return;
    }
    sound.sound_click = sfSound_create();
    sfSound_setBuffer(sound.sound_click, sound.buffer_click);
    sfSound_setVolume(sound.sound_click, context->w_setting[W_SOUND]);
    context->w_sound = sound;
}

void destroy_sound(sound_t sound)
{
    if (sound.sound_click)
        sfSound_destroy(sound.sound_click);
    if (sound.buffer_click)
        sfSoundBuffer_destroy(sound.buffer_click);
}
