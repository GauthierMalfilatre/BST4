/*
** EPITECH PROJECT, 2024
** music
** File description:
** all musiic fonction
*/
#include "wolf.h"

int add_sound(sounds_t **head, const char *name, const char *file)
{
    sounds_t *new = malloc(sizeof(sounds_t));

    if (!new) {
        return ERROR;
    }
    new->name = strdup(name);
    new->soundbuffer = sfSoundBuffer_createFromFile(file);
    new->sound = sfSound_create();
    if (!new->name || !new->sound || !new->soundbuffer) {
        printf("Error when sound %s.\n", file);
        free(new);
        return ERROR;
    }
    sfSound_setBuffer(new->sound, new->soundbuffer);
    new->next = *head;
    *head = new;
    return OK;
}

void destroy_sounds(sounds_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        destroy_sounds(head->next);
    }
    sfSound_destroy(head->sound);
    sfSoundBuffer_destroy(head->soundbuffer);
    free(head);
    return;
}

sounds_t *get_sound(sounds_t *head, const char *name)
{
    for (sounds_t *temp = head; temp; temp = temp->next) {
        if (!my_strcmp(temp->name, name)) {
            return temp;
        }
    }
    return (sounds_t *) 0;
}

void play_if_exists(sounds_t *head, const char *name)
{
    sfSound *sound = 0;

    for (sounds_t *temp = head; temp; temp = temp->next) {
        if (!my_strcmp(temp->name, name)) {
            sound = temp->sound;
        }
    }
    if (sound && sfSound_getStatus(sound) != sfPlaying) {
        sfSound_play(sound);
    }
    return;
}
