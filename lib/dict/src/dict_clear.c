/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Clear the dict
*/
#include "../include/dict.h"

void dict_clear(dict_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        dict_clear(head->next);
    }
    free(head->key);
    free(head);
    return;
}
