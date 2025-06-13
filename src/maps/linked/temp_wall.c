/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"

void add_temp_wall(temp_wall_t **head, int i, wall_t wall)
{
    temp_wall_t *new = malloc(sizeof(temp_wall_t));

    if (!new) {
        return;
    }
    new->index = i;
    new->wall = wall;
    new->next = *head;
    *head = new;
    return;
}

void resolve_others_temp_wall_index(temp_wall_t *head, const int index)
{
    for (temp_wall_t *temp = head; temp; temp = temp->next) {
        if (temp->index > index) {
            temp->index--;
        }
    } 
}

void destoy_temp_walls(temp_wall_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        destoy_temp_walls(head->next);
    }
    free(head);
    return;
}
