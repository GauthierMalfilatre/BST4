/*
** EPITECH PROJECT, 2024
** IS_WORD_IN_WORD_ARRAY
** File description:
** Find if a string is in a word array
*/
#include "my.h"

int is_word_in_word_array(char **array, char *to_find)
{
    for (int i = 0; i[array]; ++i) {
        if (!my_strcmp(i[array], to_find)) {
            return 1;
        }
    }
    return 0;
}
