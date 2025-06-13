/*
** EPITECH PROJECT, 2024
** MINI_PRINTF
** File description:
** mini_printf
*/
#include "mini_printf.h"
#include <stdarg.h>

const struct redirect_s redirect[] = {
    {'s', &my_putstr_med},
    {'i', &my_putnbr_med},
    {'d', &my_putnbr_med},
    {'%', &my_putpercent_med},
    {'c', &my_putchar_med}
};

static int redirect_func(int fd, char c, va_list list, int *sum)
{
    for (int i = 0; i < 5; i++) {
        if (c == redirect[i].form) {
            *sum += redirect[i].pointput(fd, list);
            break;
        }
    }
    return 0;
}

static int check_basic_flag(char c)
{
    for (int i = 0; i < 5; i++) {
        if (c == redirect[i].form) {
            return 1;
        }
    }
    return 0;
}

static int check_format_is_valid(char const *format)
{
    int chopped = 0;

    for (int i = 0; format[i]; i++) {
        if (format[i] == '%' && (!format[i + 1]
            || !check_basic_flag(format[i + 1]))) {
            return 1;
        }
        if (format[i] == '%') {
            i++;
        }
    }
    return 0;
}

int mini_fprintf(int fd, char const *format, ...)
{
    va_list list;
    int sum = 0;

    if (check_format_is_valid(format)) {
        return -1;
    }
    va_start(list, format);
    for (int i = 0; format[i]; i++) {
        if (format[i] == '%' && format[i + 1]) {
            redirect_func(fd, format[i + 1], list, &sum);
            i++;
        } else {
            sum += my_fputchar(fd, format[i]);
        }
    }
    va_end(list);
    return sum;
}
