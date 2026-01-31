/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Dump the dictionnary
*/
#include "../include/dict.h"

void dict_dump(dict_t *head)
{
    for (dict_t *temp = head; temp; temp = temp->next) {
        printf("|%s => %p\n", temp->key, temp->item);
    }
    return;
}
