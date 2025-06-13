/*
** EPITECH PROJECT, 2024
** MINI_PRINTF
** File description:
** mini_printf
*/
#ifndef MINI_PRINTF_H
    #define MINI_PRINTF_H
    #include <stdarg.h>

struct redirect_s {
    char form;
    int (*pointput)();
};

int mini_fprintf(int fd, const char *format, ...);

int my_strlen(char *str);

int my_fputnbr(int fd, int nb);
int my_fputchar(int fd, char c);
int my_fputstr(int fd, char *str);

int my_putstr_med(int fd, va_list list);
int my_putchar_med(int fd, va_list list);
int my_putnbr_med(int fd, va_list list);
int my_putpercent_med(int fd, va_list list);

#endif
