/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Pull lifo
*/
#include "liblifo.h"

static void pop_lifo(lifo_linked_list_t **lifo, lifo_linked_list_t *node)
{
    *lifo = node->next;
    free(node);
    return;
}

void *pull_lifo(lifo_t *lifo)
{
    void *temp;

    if (!lifo->lifo || lifo->size_of_lifo < 1) {
        return 0;
    }
    temp = lifo->lifo->stuff;
    pop_lifo(&lifo->lifo, lifo->lifo);
    --lifo->size_of_lifo;
    return temp;
}
