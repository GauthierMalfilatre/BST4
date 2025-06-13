/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** sound header
*/


#ifndef SOUND_H
    #define SOUND_H

    #include "wolf.h"

void destroy_music(wolf_context_t *context);
void play_music(wolf_context_t *context, const char *path, sfBool repeat);

sounds_t *get_sound(sounds_t *head, const char *name);
void play_sound(sfSound *sound);
void create_sound(wolf_context_t *context);
void destroy_sound(sound_t sound);

int add_sound(sounds_t **head, const char *name, const char *file);
int play_sound_name(sounds_t *head, const char *name);
void destroy_sounds(sounds_t *head);

void play_force(sfSound *sound);
void play_if_exists(sounds_t *head, const char *name);

#endif /*SOUND_H*/
