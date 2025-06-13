/*
** EPITECH PROJECT, 2024
** MY_STRLEN
** File description:
** Returns the size of an integer
*/
#include "my.h"

int my_strlen(char const *str)
{
    int length = 0;

    if (!str)
        return length;
    for (; str[length]; length++);
    return length;
}
