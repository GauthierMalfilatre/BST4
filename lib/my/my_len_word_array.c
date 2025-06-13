/*
** EPITECH PROJECT, 2024
** MY_LEN_WORD_ARRAY
** File description:
** Len a word array
*/
#include "my.h"

int my_len_word_array(char **array)
{
    int len = 0;

    for (int i = 0; array[i]; ++i) {
        ++len;
    }
    return len;
}
