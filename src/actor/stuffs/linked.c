/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

void add_stuff(stuffs_t **head, sfVector2f pos, const int type)
{
    stuffs_t *bullet = malloc(sizeof(stuffs_t));

    if (!bullet) {
        return;
    }
    bullet->type = type;
    bullet->pos = pos;
    bullet->next = *head;
    *head = bullet;
    return;
}

void destroy_stuffs(stuffs_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        destroy_stuffs(head->next);
    }
    free(head);
    return;
}
