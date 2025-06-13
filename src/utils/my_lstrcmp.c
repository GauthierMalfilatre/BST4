/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** my_lstrcmp
*/
#include "wolf.h"

static char lower(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return c - ('A' - 'a');
    }
    return c;
}

int my_lstrcmp(const char *s1, const char *s2)
{
    int i = 0;

    for (; s1[i] && s2[i] && lower(s1[i]) == lower(s2[i]); i++);
    return s1[i] - s2[i];
}
