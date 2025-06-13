/*
** EPITECH PROJECT, 2024
** MY_COMPUTE_POWER_REC
** File description:
** Tiny recursive power calculator - kinda ez
*/
#include "my.h"

int ifree(void *to_free)
{
    if (to_free) {
        free(to_free);
    }
    return 0;
}
