/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Main file for RAY engine v4.
** Movement of players
*/
#include "wolf.h"

void add_bullet(bullet_t **head, player_t *player)
{
    bullet_t *bullet = malloc(sizeof(bullet_t));
    float dispersion[] = {0.00f, 0.05f, 0.10f, 0.30f};
    float angle_offset = ((float)rand() / RAND_MAX - 0.5f)
        * dispersion[player->infos.rdi];

    bullet->player = player;
    bullet->prev = 0;
    bullet->next = *head;
    if (*head) {
        (*head)->prev = bullet;
    }
    bullet->dir = (sfVector2f) {-1 * sin(*player->angle + angle_offset),
        cos(*player->angle + angle_offset)};
    bullet->pos = (sfVector2f){*player->x, *player->y};
    bullet->speed = 100;
    bullet->clock = sfClock_create();
    *head = bullet;
    return;
}

void destroy_bullet(bullet_t **head, bullet_t *self)
{
    if (self->prev) {
        self->prev->next = self->next;
    } else {
        *head = self->next;
    }
    if (self->next) {
        self->next->prev = self->prev;
    }
    sfClock_destroy(self->clock);
    free(self);
    return;
}

void destroy_bullets(bullet_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        destroy_bullets(head->next);
    }
    sfClock_destroy(head->clock);
    free(head);
    return;
}
