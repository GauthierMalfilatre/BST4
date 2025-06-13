/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Parse main file for configuration
*/
#include "wolf.h"
#include "parser.h"

static const point_parse_t tab[1] = {
    {"texture", &check_if_texture_exists},
};

static int find(char **warray, wolf_context_t *context, int *error)
{
    for (int i = 0; i < 1; i++) {
        if (!my_lstrcmp(warray[0], tab[i].command)) {
            return tab[i].func(&warray[1], context, error) + 1;
        }
    }
    return 1;
}

int builtin_require(char **warray, wolf_context_t *context)
{
    int error = 0;

    for (int i = 1; i < my_len_word_array(warray) && warray[i]; i++) {
        i += find(&warray[i], context, &error);
        if (error) {
            return ERROR;
        }
    }
    return OK;
}
