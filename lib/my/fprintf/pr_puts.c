/*
** EPITECH PROJECT, 2024
** B-CPE-101-NCY-1-1-bsminiprintf-gauthier.malfilatre
** File description:
** my_puts
*/
#include "mini_printf.h"
#include <unistd.h>
#include <stdio.h>

static int my_putnbr_check(int *nb, int *sum)
{
    if (*nb == -2147483648) {
        write(1, "-2147483648", 11);
        return -1;
    }
    if (*nb < 0) {
        *nb *= -1;
        (*sum)++;
        write(1, "-", 1);
    }
    return 0;
}

int my_fputchar(int fd, char c)
{
    write(fd, &c, 1);
    return 1;
}

int my_fputstr(int fd, char *str)
{
    write(fd, str, my_strlen(str));
}

int my_fputnbr(int fd, int nb)
{
    int sum = 0;

    if (my_putnbr_check(&nb, &sum) == -1) {
        return 11;
    }
    if (nb / 10 > 0) {
        sum += my_fputnbr(fd, nb / 10);
    }
    my_fputchar(fd, nb % 10 + '0');
    return sum + 1;
}
