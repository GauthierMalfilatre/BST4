/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Header file for liblifo
*/
#include "../include/dict.h"

static void remove_node(dict_t **head, dict_t *node)
{
    if (!head || !node) {
        return;
    }
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        *head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    free(node->key);
    free(node);
    return;
}

void *dict_remove_entry(dict_t **head, const char *key)
{
    dict_t *targeted = (dict_t *) 0;
    void *stuff = (void *) 0;

    if (!head) {
        return (void *) 0;
    }
    if (dict_node_exists(*head, key, &targeted) != 1) {
        return (void *) 0;
    }
    stuff = targeted->item;
    remove_node(head, targeted);
    return stuff;
}
