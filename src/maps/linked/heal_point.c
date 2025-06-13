/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

int add_heal_point(heals_t **head, sfVector2f pos)
{
    heals_t *heal = malloc(sizeof(heals_t));

    if (!heal) {
        return ERROR;
    }
    heal->pos = pos;
    heal->is_taken = 0.f;
    heal->next = *head;
    *head = heal;
    return OK;
}

void delete_heals(heals_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        delete_heals(head->next);
    }
    free(head);
    return;
}
