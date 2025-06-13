/*
** EPITECH PROJECT, 2025
** WOLF3D
** File description:
** Create players.
*/
#include "wolf.h"
#include "math.h"

int count_messages_with_type(messages_t *messages, const message_type_t type)
{
    int i = 0;

    for (messages_t *temp = messages; temp; temp = temp->next) {
        if (temp->type == type) {
            i++;
        }
    }
    return i;
}
