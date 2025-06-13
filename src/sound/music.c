/*
** EPITECH PROJECT, 2024
** music
** File description:
** all musiic fonction
*/

#include "wolf.h"

void destroy_music(wolf_context_t *context)
{
    if (!context->w_sound.music)
        return;
    sfMusic_stop(context->w_sound.music);
    sfMusic_destroy(context->w_sound.music);
    context->w_sound.music = NULL;
}

void play_music(wolf_context_t *context, const char *path, sfBool repeat)
{
    if (!path)
        return;
    destroy_music(context);
    context->w_sound.music = sfMusic_createFromFile(path);
    if (!context->w_sound.music) {
        fprintf(stderr, "Error: Failed to load music from '%s'\n", path);
        return;
    }
    sfMusic_setVolume(context->w_sound.music, context->w_setting[W_MUSIC]);
    sfMusic_setLoop(context->w_sound.music, repeat);
    sfMusic_play(context->w_sound.music);
}
