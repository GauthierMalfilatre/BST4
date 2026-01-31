/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Just return a boolean if a dict variable exists.
*/
#include "wolf.h"
#include "utils.h"
#include "dict.h"

char dict_bool(dict_t *dict, const char *key)
{
    return (dict_search_int(dict, key) == 1);
}
