/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Clear buffs
*/
#include "wolf.h"

// Return the number of buff clears
int clear_buffs(buff_t *head)
{
    int cleared = 0;

    if (!head) {
        return 0;
    }
    if (head->next) {
        cleared = clear_buffs(head->next);
    }
    free(head);
    return 1 + cleared;
}
