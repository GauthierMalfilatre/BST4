/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Remove buff
*/
#include "wolf.h"

void remove_buff(buff_t **head, buff_t *buff)
{
    if (!head || !buff) {
        return;
    }
    if (buff->next) {
        buff->next->prev = buff->prev;
    }
    if (buff->prev) {
        buff->prev->next = buff->next;
    } else {
        *head = buff->next;
    }
    free(buff);
    return;
}
