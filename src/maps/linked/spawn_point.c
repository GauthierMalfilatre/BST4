/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

int add_spawn_point(spawns_t **head, sfVector2f a, sfVector2f b,
    spawn_type_t type)
{
    spawns_t *spawn = malloc(sizeof(spawns_t));

    if (!spawn) {
        return ERROR;
    }
    spawn->a = a;
    spawn->b = b;
    spawn->type = type;
    spawn->next = *head;
    *head = spawn;
    return OK;
}

spawns_t *find_spawn_point(spawns_t *head, spawn_type_t type)
{
    for (spawns_t *temp = head; temp; temp = temp->next) {
        if (temp->type == type) {
            return temp;
        }
    }
    return (spawns_t *) 0;
}

void delete_spawns(spawns_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        delete_spawns(head->next);
    }
    free(head);
    return;
}
