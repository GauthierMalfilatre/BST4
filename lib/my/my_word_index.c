/*
** EPITECH PROJECT, 2024
** MY_STR_TO_WORD_ARRAY
** File description:
** Find index of a word in a word array.
*/
#include "my.h"

int word_index(char **array, char *to_find)
{
    int index = 0;

    for (; array[index] && my_strcmp(array[index], to_find); ++index);
    if (index >= my_len_word_array(array)) {
        return 0;
    }
    return index;
}
