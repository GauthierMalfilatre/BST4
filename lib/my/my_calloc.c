/*
** EPITECH PROJECT, 2024
** Hugo MARTIN Lib
** File description:
** my calloc function
*/

#include <stdlib.h>

void *my_calloc(size_t nb, size_t size)
{
    size_t total_size = nb * size;
    unsigned char *ptr = malloc(total_size);

    if (!ptr)
        return NULL;
    for (size_t i = 0; i < total_size; i++)
        ptr[i] = 0;
    return ptr;
}
