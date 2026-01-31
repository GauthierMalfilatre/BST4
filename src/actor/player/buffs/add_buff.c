/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add a buff
*/
#include "wolf.h"

void add_buff(buff_t **head, buff_type_t type, long double value,
    long double duration)
{
    buff_t *new_buff = (buff_t *) 0;

    if (!head) {
        return;
    }
    new_buff = malloc(sizeof(buff_t));
    if (!new_buff) {
        return;
    }
    new_buff->next = *head;
    new_buff->prev = (buff_t *) 0;
    if (*head) {
        (*head)->prev = new_buff;
    }
    new_buff->is_first_time = 1;
    new_buff->type = type;
    new_buff->value = value;
    new_buff->duration = duration;
    *head = new_buff;
    return;
}
