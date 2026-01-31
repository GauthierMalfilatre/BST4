/*
** EPITECH PROJECT, 2025
** LIBLIFO
** File description:
** Header file for liblifo
*/
#include "../include/dict.h"

dict_t *__dict_add_entry(dict_t **head, const char *key, void *stuff)
{
    dict_t *new = (dict_t *) 0;
    char *dupkey = (char *) 0;

    if (!head || dict_node_exists(*head, key, (dict_t **) 0) == 1) {
        return NULL;
    }
    new = malloc(sizeof(dict_t));
    dupkey = strdup(key);
    if (!new || !dupkey) {
        return NULL;
    }
    if (*head)
        (*head)->prev = new;
    new->prev = (dict_t *) 0;
    new->next = *head;
    new->key = dupkey;
    new->item = stuff;
    *head = new;
    return *head;
}
