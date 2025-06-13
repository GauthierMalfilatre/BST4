/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Delete lifo
*/
#include "liblifo.h"

int del_lifo(lifo_t *lifo)
{
    while (lifo->size_of_lifo > 0 && lifo->lifo) {
        pull_lifo(lifo);
    }
    free(lifo);
}
