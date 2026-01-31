/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Clear the dict
*/
#include "../include/dict.h"

void *__dict_change_entry(dict_t *head, char const *key, void *new)
{
    dict_t *node = NULL;
    void *value = NULL;

    if (dict_node_exists(head, key, &node) != 1) {
        return NULL;
    }
    value = node->item;
    node->item = new;
    return value;
}
