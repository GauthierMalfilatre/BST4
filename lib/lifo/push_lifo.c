/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Push lifo
*/
#include "liblifo.h"

static int add_lifo(lifo_linked_list_t **lifo, void *value)
{
    lifo_linked_list_t *new_stuff = malloc(sizeof(lifo_linked_list_t));

    if (!new_stuff) {
        return -1;
    }
    new_stuff->stuff = value;
    new_stuff->next = *lifo;
    *lifo = new_stuff;
    return 0;
}

int push_lifo(lifo_t *lifo, void *stuff)
{
    if (add_lifo(&lifo->lifo, stuff) == -1) {
        return -1;
    }
    ++lifo->size_of_lifo;
    return 0;
}
