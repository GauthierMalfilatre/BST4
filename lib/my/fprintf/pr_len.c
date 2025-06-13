/*
** EPITECH PROJECT, 2024
** pr_len
** File description:
** Lens functions for mini_printf
*/
#include "mini_printf.h"
#include <stdarg.h>

int my_strlenrec(char *str)
{
    return *str ? 1 + my_strlen(str) : 0;
}
