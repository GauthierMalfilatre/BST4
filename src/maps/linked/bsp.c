/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Add player with parsing
*/
#include "wolf.h"
#include <string.h>

int add_bsp(bsp_t **head, sfVector2f a, sfVector2f b)
{
    bsp_t *spawn = malloc(sizeof(bsp_t));

    if (!spawn) {
        return ERROR;
    }
    spawn->a = a;
    spawn->b = b;
    spawn->center.x = a.x + (b.x - a.x) / 2;
    spawn->center.y = a.y + (b.y - a.y) / 2;
    spawn->next = *head;
    *head = spawn;
    return OK;
}

sfBool is_in_bsp(player_t *player, bsp_t *bsps)
{
    for (bsp_t *temp = bsps; temp; temp = temp->next) {
        if (*player->x > temp->a.x && *player->y > temp->a.y &&
            *player->x < temp->b.x && *player->y < temp->b.y) {
            return sfTrue;
        }
    }
    return sfFalse;
}

void delete_bsp(bsp_t *head)
{
    if (!head) {
        return;
    }
    if (head->next) {
        delete_bsp(head->next);
    }
    free(head);
    return;
}
