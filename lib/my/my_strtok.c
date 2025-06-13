/*
** EPITECH PROJECT, 2024
** Hugo MARTIN Lib
** File description:
** my strtok function
*/

#include "my.h"

char *my_strtok(char *str, const char delim)
{
    static char *next = NULL;
    char *start = NULL;

    if (str != NULL)
        next = str;
    if (next == NULL)
        return NULL;
    start = next;
    while (*next && *next != delim)
        next++;
    if (*next) {
        *next = '\0';
        next++;
    } else
        next = NULL;
    return start;
}
