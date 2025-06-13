/*
** EPITECH PROJECT, 2024
** LEN_WORDS_IN_WORD_ARRAY
** File description:
** Len number of words equal to given in word array
*/
#include "my.h"

int len_words_in_word_array(char **array, char *key)
{
    int count = 0;

    for (int i = 0; i[array]; ++i) {
        if (!my_strcmp(i[array], key)) {
            ++count;
        }
    }
    return count;
}
