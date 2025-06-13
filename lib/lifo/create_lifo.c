/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Create lifo
*/
#include "liblifo.h"

lifo_t *create_lifo(void)
{
    lifo_t *new_lifo = malloc(sizeof(lifo_t));

    if (!new_lifo) {
        return (lifo_t *) 0;
    }
    new_lifo->size_of_lifo = 0;
    new_lifo->lifo = (lifo_linked_list_t *) 0;
    return new_lifo;
}
