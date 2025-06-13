/*
** EPITECH PROJECT, 2024
** MY_STR_TO_WORD_ARRAY_2
** File description:
** Version 2 of my_str_to_word_array
*/
#include "my.h"


static int is_valid(const char c)
{
    return c != '\t' && c != ' ';
}

static int len_word(const char *str)
{
    int len = 0;

    for (; str[len] && is_valid(str[len]); len++);
    return len;
}

static int count_words(const char *str)
{
    int len = 0;

    for (int i = 0; str[i]; i++) {
        if ((!i && is_valid(str[i])) || (is_valid(str[i]) &&
            !is_valid(str[i - 1]))) {
            len++;
        }
    }
    return len;
}

char **my_str_to_word_array2(const char *str)
{
    char **array = malloc(sizeof(char *) * (count_words(str) + 1));
    int actual_array = 0;
    const int size_of = my_strlen(str);

    for (int i = 0; str[i] && i < size_of; i++) {
        if (!is_valid(str[i])) {
            continue;
        }
        array[actual_array] = my_strndup(&str[i], len_word(&str[i]));
        i += my_strlen(array[actual_array]);
        actual_array++;
    }
    array[actual_array] = (void *) 0;
    return array;
}
