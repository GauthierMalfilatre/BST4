/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Header file for liblifo
*/
#include "../include/dict.h"

static void filler(dict_t **targeted, dict_t *temp)
{
    if (targeted) {
        *targeted = temp;
    }
}

int dict_node_exists(dict_t *head, const char *key, dict_t **targeted)
{
    if (!head) {
        return -1;
    }
    for (dict_t *temp = head; temp; temp = temp->next) {
        if (!strcmp(key, temp->key)) {
            filler(targeted, temp);
            return 1;
        }
    }
    return 0;
}

void *dict_search_entry(dict_t *head, const char *key)
{
    dict_t *targeted = (dict_t *) 0;

    if (dict_node_exists(head, key, &targeted) != 1) {
        return (void *) 0;
    }
    return targeted->item;
}
