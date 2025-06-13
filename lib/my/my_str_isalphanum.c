/*
** EPITECH PROJECT, 2025
** Hugo martin tek 1
** File description:
** check if str is alphanum
*/

int my_str_is_alphanum(char *str)
{
    char c = 0;

    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        c = str[i];
        if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122) ||
        (c >= '0' && c <= '9')))
            return 0;
    }
    return 1;
}
