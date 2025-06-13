/*
** EPITECH PROJECT, 2024
** MY_LEN_WORD_ARRAY
** File description:
** Dup a word array until n
*/
#include "my.h"

char **my_ndup_word_array(char **array, int len)
{
    char **new = malloc(sizeof(char *) * (len + 1));
    int i = 0;

    for (; i[array] && i < len; ++i) {
        i[new] = my_strdup(i[array]);
    }
    i[new] = (char *) 0;
    return new;
}

char **my_dup_word_array_until(char **array, char *to_find)
{
    int index = 0;

    for (; array[index] && my_strcmp(array[index], to_find); ++index);
    return my_ndup_word_array(array, index);
}
