/*
** EPITECH PROJECT, 2025
** MY_srcSPLIT
** File description:
** Split an src
*/
#include "my.h"

static int is_valid(const char c, const char delim)
{
    return c != delim;
}

static int len_word(const char *src, const char delim)
{
    int len = 0;

    for (; src[len] && is_valid(src[len], delim); len++);
    return len;
}

static int count_words(const char *src, const char delim)
{
    int len = 0;

    for (int i = 0; src[i]; i++) {
        if ((!i && is_valid(src[i], delim)) || (is_valid(src[i], delim) &&
            !is_valid(src[i - 1], delim))) {
            len++;
        }
    }
    return len;
}

char **my_strsplit(const char *src, const char delim)
{
    char **array = malloc(sizeof(char *) * (count_words(src, delim) + 1));
    int actual_array = 0;
    const int size_of = my_strlen(src);

    for (int i = 0; i < size_of && src[i]; i++) {
        if (!is_valid(src[i], delim)) {
            continue;
        }
        array[actual_array] = my_strndup(&src[i], len_word(&src[i], delim));
        i += my_strlen(array[actual_array]);
        actual_array++;
    }
    array[actual_array] = (void *) 0;
    return array;
}
