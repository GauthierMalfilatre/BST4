/*
** EPITECH PROJECT, 2024
** DISP_STDARG_SUB
** File description:
** disp_stdarg_sub
*/
#include "mini_printf.h"
#include <stdarg.h>

int my_putstr_med(int fd, va_list list)
{
    return my_fputstr(fd, va_arg(list, char *));
}

int my_putnbr_med(int fd, va_list list)
{
    return my_fputnbr(fd, va_arg(list, int));
}

int my_putchar_med(int fd, va_list list)
{
    return my_fputchar(fd, va_arg(list, int));
}

int my_putpercent_med(int fd, va_list list)
{
    return my_fputchar(fd, '%');
}
