/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Destroy the context for having no memory leaks
*/
#include "wolf.h"
#include "sound.h"
#include "scenes.h"

void destroy_context(wolf_context_t *context)
{
    if (!context)
        return;
    destroy_sounds(context->w_sound.sounds);
    destroy_maps(context->maps, context->n_map);
    destroy_players(context->players, context->n_players);
    destroy_characters(context->characters, context->n_chars);
    destroy_view(context->view);
    if (scenes[context->current_scene].id)
        scenes[context->current_scene].destroy(context);
    if (context->textures)
        destroy_textures(context->textures);
    if (context->w_sound.music)
        destroy_music(context);
    if (context->w_sound.sound_click)
        destroy_sound(context->w_sound);
    ifree(context);
    return;
}
