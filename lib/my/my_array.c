/*
** EPITECH PROJECT, 2024
** my_array
** File description:
** some function for array
*/

#include <stdlib.h>
#include "my.h"

int my_size_array(void **array)
{
    int i = 0;

    for (; array[i]; i++) {
        i++;
    }
    return i;
}

void free_array(void **array)
{
    if (!array)
        return;
    for (int i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);
}

void free_narray(void **array, int n)
{
    if (!array)
        return;
    for (int i = 0; i < n; i++) {
        free(array[i]);
    }
    free(array);
}
